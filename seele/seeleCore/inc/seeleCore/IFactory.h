#pragma once

#include <memory>

#include "IAudioProcessor.h"
#include "IAnalysis.h"
#include "ISynthesis.h"

namespace hidonash
{
    class IFactory
    {
    public:
        virtual ~IFactory() = default;

        virtual AudioProcessorPtr createEngine(std::atomic<float>& pitchRatio, double sampleRate) const = 0;

        virtual AnalysisPtr createAnalysis(int freqPerBin) const = 0;

        virtual SynthesisPtr createSynthesis(int freqPerBin, AnalysisPtr analysis) const = 0;
    };

    using FactoryPtr = std::unique_ptr<IFactory>;
}
