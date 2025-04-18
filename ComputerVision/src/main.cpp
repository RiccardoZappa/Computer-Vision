#include <opencv2/opencv.hpp>
#include <onnxruntime_cxx_api.h>
#include <numeric>

#include "camera/cameraGrabber.hpp"
#include "camera/frameProcessor.hpp"
#include "core/detector.hpp"

using namespace Camera;
using namespace Core;

constexpr wchar_t* modelPath = L"C:/Computer-Vision/ComputerVision/model/yolov8n.onnx";


const float CONFIDENCE_THRESHOLD = 0.5f;
const float NMS_THRESHOLD = 0.4f;
const int NUM_CLASSES = 80; // Assuming COCO dataset (adjust if different)

// Optional: Define class names (replace with your actual class names)
const std::vector<std::string> class_names = {
    "person", "bicycle", "car", "motorcycle", "airplane", "bus", "train", "truck", "boat",
    "traffic light", "fire hydrant", "stop sign", "parking meter", "bench", "bird", "cat", "dog",
    "horse", "sheep", "cow", "elephant", "bear", "zebra", "giraffe", "backpack", "umbrella",
    "handbag", "tie", "suitcase", "frisbee", "skis", "snowboard", "sports ball", "kite",
    "baseball bat", "baseball glove", "skateboard", "surfboard", "tennis racket", "bottle",
    "wine glass", "cup", "fork", "knife", "spoon", "bowl", "banana", "apple", "sandwich",
    "orange", "broccoli", "carrot", "hot dog", "pizza", "donut", "cake", "chair", "couch",
    "potted plant", "bed", "dining table", "toilet", "tv", "laptop", "mouse", "remote",
    "keyboard", "cell phone", "microwave", "oven", "toaster", "sink", "refrigerator", "book",
    "clock", "vase", "scissors", "teddy bear", "hair drier", "toothbrush"
};




int64_t vectorProduct(const std::vector<int64_t>& vector)
{
    if(vector.size() == 0) 
        return 0;
    return std::accumulate(vector.begin(), vector.end(), 1LL, std::multiplies<int64_t>());
}

int main() 
{
    CameraGrabber grabber{};

    Detector detector{};

    auto videoCapture = grabber.getVideoCapture();
    int deviceID = 0;
    int ApiID = cv::CAP_ANY;

    videoCapture.open(deviceID, ApiID);

    cv::Mat frame;
    Ort::MemoryInfo memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    std::vector<Ort::Value> ort_inputs; // Vector to hold input tensors (usually just one)
    ort_inputs.reserve(1); // Reserve space for efficiency

    //input preparation
    const char* input_name = "images"; // Replace "images" with the actual input node name from Netron
    std::vector<int64_t> input_dims = {1, 3, 640, 640}; // NCHW format as specified
    ONNXTensorElementDataType input_type = ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT; // float32
    long long input_tensor_size = vectorProduct(input_dims); // Calculate expected elements: 1*3*640*640

    // output preparation
    const char* output_name = "output0"; // Replace "output0" with the actual output node name from Netron
    std::vector<int64_t> output_dims = {1, 84, 8400}; // As specified
    ONNXTensorElementDataType output_type = ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT; // float32
    long long output_tensor_size = vectorProduct(output_dims); // Calculate expected elements: 1*84*8400

    // Prepare C-style string arrays for Run() API
    std::vector<const char*> input_node_names = {input_name};
    std::vector<const char*> output_node_names = {output_name};

    detector.initialize(modelPath);

    while(videoCapture.read(frame))
    {
        cv::Mat blob;

        FrameProcessor::ProcessFrame(frame, blob);

        // --- 4. Verify Blob Shape and Type (Optional) ---
        // Note: blob.size is a special object. Access dimensions via blob.size[index]
        std::cout << "Blob Info:" << std::endl;
        std::cout << "  Dimensions: " << blob.dims << std::endl; // Should be 4
        std::cout << "  Shape: [" << blob.size[0] << ", " << blob.size[1] << ", "
                  << blob.size[2] << ", " << blob.size[3] << "]" << std::endl; // Should be [1, 3, 640, 640]
        std::cout << "  Type: " << blob.type() << " (CV_32F=" << CV_32F << ")" << std::endl; // Should be 5 (CV_32F)
        std::cout << "  Total elements: " << blob.total() << std::endl; // 1*3*640*640 = 1228800
        std::cout << "  Is continuous: " << std::boolalpha << blob.isContinuous() << std::endl;

                // --- 5. Create Ort::Value from cv::Mat Blob ---
        // CreateTensor wraps the existing blob data. No data copy involved here for CPU.
        // The blob variable must stay in scope and not be modified until Run() returns.
        ort_inputs.clear(); // Clear previous frame's tensor
        ort_inputs.emplace_back(Ort::Value::CreateTensor<float>(
            memory_info,                  // Specifying CPU memory
            blob.ptr<float>(),            // Pointer to blob data
            blob.total(),                 // Total number of elements in the blob
            input_dims.data(),            // Pointer to the dimension array
            input_dims.size()             // Number of dimensions
        ));



        // --- 6. Run Inference ---
        try {
            auto output_tensors = detector.runInference(
                Ort::RunOptions{nullptr},
                input_node_names.data(),   // Hardcoded input name
                ort_inputs.data(),
                ort_inputs.size(),
                output_node_names.data(),  // Hardcoded output name
                output_node_names.size()
            );

            // --- 7. Process Output ---
            if (!output_tensors.empty() && output_tensors.IsTensor()) {
                // You can optionally verify the output shape against your known output_dims
                auto& output_tensor = output_tensors;
                auto received_shape_info = output_tensor.GetTensorTypeAndShapeInfo();
                auto received_shape = received_shape_info.GetShape();
                size_t received_elements = received_shape_info.GetElementCount();

                if (received_shape!= output_dims || received_elements!= static_cast<size_t>(output_tensor_size)) {
                     std::cerr << "Warning: Output shape/size mismatch! Expected: , Got: [";
                     for(size_t i = 0; i < received_shape.size(); ++i) std::cout << received_shape[i] << " ";
                     std::cout << "]" << std::endl;
                }

                // Get pointer to output data (assuming float output)
                float* output_data = output_tensor.GetTensorMutableData<float>();

                // Process the output_data (size = 1*84*8400 elements)
                std::cout << "Processed frame. Output elements: " << received_elements << std::endl;
                //... your post-processing logic...

            }


            std::vector<cv::Rect> boxes;
            std::vector<float> confidences;
            std::vector<int> class_ids;

            const int num_proposals = static_cast<int>(output_shape); // 8400
            const int num_params_per_proposal = static_cast<int>(output_shape); // 84

            // Get scaling factors to map model output coordinates back to original frame size
            float scale_x = static_cast<float>(frame.cols) / input_dims[8]; // frame_width / model_input_width
            float scale_y = static_cast<float>(frame.rows) / input_dims[7]; // frame_height / model_input_height

            for (int i = 0; i < num_proposals; ++i) {
                // Pointer to the start of data for the i-th proposal
                // output_data points to the beginning of the flat array.
                // Accessing element [batch=0, param=j, proposal=i] requires careful indexing:
                // index = batch_offset + param_offset + proposal_offset
                // index = 0 * (num_params_per_proposal * num_proposals) + j * num_proposals + i
                // Since batch=0, index = j * num_proposals + i

                // Extract class scores (first NUM_CLASSES elements after the 4 box coordinates)
                float* class_scores_ptr = output_data + (4 * num_proposals) + i;
                auto max_score_it = std::max_element(class_scores_ptr, class_scores_ptr + (NUM_CLASSES * num_proposals), [&](float a, float b){
                    // Need to step by num_proposals to compare scores for the same proposal 'i' across different classes 'j'
                    return a < b;
                });

                // Find the class ID and the max score
                int class_id = -1;
                float max_score = 0.0f;
                for(int j = 0; j < NUM_CLASSES; ++j) {
                    float score = output_data[(4 + j) * num_proposals + i];
                    if (score > max_score) {
                        max_score = score;
                        class_id = j;
                    }
                }


                if (max_score > CONFIDENCE_THRESHOLD) {
                    // Extract box coordinates (cx, cy, w, h)
                    float cx = output_data[0 * num_proposals + i];
                    float cy = output_data[1 * num_proposals + i];
                    float w = output_data[2 * num_proposals + i];
                    float h = output_data[3 * num_proposals + i];

                    // Convert center coordinates and dimensions to top-left corner (x, y)
                    int x = static_cast<int>((cx - w / 2.0f) * scale_x);
                    int y = static_cast<int>((cy - h / 2.0f) * scale_y);
                    int width = static_cast<int>(w * scale_x);
                    int height = static_cast<int>(h * scale_y);

                    boxes.push_back(cv::Rect(x, y, width, height));
                    confidences.push_back(max_score);
                    class_ids.push_back(class_id);
                }
            }

            // Apply Non-Maximum Suppression
            std::vector<int> nms_indices;
            cv::dnn::NMSBoxes(boxes, confidences, CONFIDENCE_THRESHOLD, NMS_THRESHOLD, nms_indices);

            // Draw the final bounding boxes
            for (int idx : nms_indices) {
                cv::Rect box = boxes[idx];
                int class_id = class_ids[idx];
                float confidence = confidences[idx];

                // Draw rectangle
                cv::rectangle(frame, box, cv::Scalar(0, 255, 0), 2);

                // Prepare label text
                std::string label = "Unknown";
                if (class_id >= 0 && class_id < class_names.size()) {
                    label = class_names[class_id];
                }
                label += ": " + cv::format("%.2f", confidence);

                // Put label text above the rectangle
                int baseline = 0;
                cv::Size label_size = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseline);
                cv::rectangle(frame,
                              cv::Point(box.x, box.y - label_size.height - baseline),
                              cv::Point(box.x + label_size.width, box.y),
                              cv::Scalar(0, 255, 0), cv::FILLED);
                cv::putText(frame, label, cv::Point(box.x, box.y - baseline),
                            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0), 1, cv::LINE_AA);
            }

        } catch (const Ort::Exception& exception) {
            std::cerr << "ERROR running inference: " << exception.what() << std::endl;
        }

        cv::imshow("RealTime detection", frame);
        if(cv::waitKey(1) == 'q') break;
    }
    videoCapture.release();
    cv::destroyAllWindows();
    return 0;
}