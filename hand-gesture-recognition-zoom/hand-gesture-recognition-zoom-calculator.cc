#include <cmath>
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/rect.pb.h"
#include<sstream>
namespace mediapipe
{
    namespace
    {
        constexpr char normRectTag[] = "NORM_RECTS";
        constexpr char RENDERDATATag[] = "GESTURE";
    } // namespace

    // Graph config:
    // node {
    //     calculator: "HandZoomGestureRecognitionCalculator"
    //     input_stream: "NORM_RECTS:multi_hand_rects"
    //     output_stream: "GESTURE:zoom_gesture"
    // }
    class HandZoomGestureRecognitionCalculator : public CalculatorBase
    {
    public:
        static ::mediapipe::Status GetContract(CalculatorContract *cc);
        ::mediapipe::Status Open(CalculatorContext *cc) override;

        ::mediapipe::Status Process(CalculatorContext *cc) override;

    private:
        float previous_rectangle_height;
        float scaleFactor;
        float minZoom = 0.473138, maxZoom = 0.903992;
    };

    REGISTER_CALCULATOR(HandZoomGestureRecognitionCalculator);

    ::mediapipe::Status HandZoomGestureRecognitionCalculator::GetContract(
        CalculatorContract *cc)
    {
        if (cc->Inputs().HasTag(normRectTag)) {
            cc->Inputs().Tag(normRectTag).Set<std::vector<NormalizedRect>>();
        }

        cc->Outputs().Tag(RENDERDATATag).Set< std::vector<std::string> >();

        return ::mediapipe::OkStatus();
    }

    ::mediapipe::Status HandZoomGestureRecognitionCalculator::Open(
        CalculatorContext *cc)
    {
        cc->SetOffset(TimestampDiff(0));
        return ::mediapipe::OkStatus();
    }

    ::mediapipe::Status HandZoomGestureRecognitionCalculator::Process(
        CalculatorContext *cc)
    {

        const auto& rects =
            cc->Inputs().Tag(normRectTag).Get<std::vector<NormalizedRect>>();

        const auto rect = rects[0];
        float height = rect.height();

        std::string recognized_hand_gesture;

        // LOG(INFO) << "Height " << height;

        // Zoom min/max
        if(height < minZoom)
        {
            height = minZoom;
        }else if(height > maxZoom){
            height = maxZoom;
        }
        scaleFactor = ((height - minZoom) / (maxZoom - minZoom));
        int factor = scaleFactor * 100;

        // convert integer to string
        std::stringstream ss;
        ss << factor;
        std::string s;
        ss >> s;

        // LOG(INFO) << "Factor " << factor;
        recognized_hand_gesture = "Zoom " + s;

        // LOG(INFO) << "Zoom hand identification " << recognized_hand_gesture;

        //set text
        std::vector<std::string> *labelVector = new std::vector<std::string>();;
        labelVector->push_back(recognized_hand_gesture);

        cc->Outputs()
            .Tag(RENDERDATATag)
            .Add(labelVector, cc->InputTimestamp());

            return ::mediapipe::OkStatus();

    }   // namespace mediapipe
} // namespace mediapipe