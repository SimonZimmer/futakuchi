#pragma once

#include <array>

#include <juce_dsp/juce_dsp.h>

#include <core/AudioBuffer.h>

#include "IAudioProcessor.h"

namespace hidonash
{
    class PitchShifter
    {
    public:
        PitchShifter(double sampleRate);
        ~PitchShifter() = default;

        void process(core::AudioBuffer<float>& audioBuffer);

        void setPitchRatio(float pitchRatio);

        void setFftFrameSize(float fftFrameSize);

        void fft(juce::dsp::Complex<float>* fftBuffer, bool inverse);

    private:
        void analysis(int freqPerBin, double expectedPhaseDifference);
        void synthesis(int freqPerBin, double expectedPhaseDifference);

        float pitchFactor_{ 0.f };
        double sampleRate_;
        size_t fftFrameSize_;

        std::array<float, 8192> fifoIn_;
        std::array<float, 8192> fifoOut_;
        std::array<float, 8192/2+1> lastPhase_;
        std::array<float, 8192/2+1> sumPhase_;
        std::array<float, 2*8192> outputAccumulationBuffer_;
        std::array<float, 8192> analysisFrequencyBuffer_;
        std::array<float, 8192> analysisMagnitudeBuffer_;
        std::array<float, 8192> synthesisFrequencyBuffer_;
        std::array<float, 8192> synthesisMagnitudeBuffer_;

        std::array<juce::dsp::Complex<float>, 2*8192> fftWorkspace_;
        std::unique_ptr<juce::dsp::FFT> fft_;
    };

}
