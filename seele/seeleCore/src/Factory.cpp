#include "Factory.h"
#include "Engine.h"
#include "Analysis.h"
#include "Synthesis.h"

namespace hidonash
{
    AudioProcessorPtr
    Factory::createEngine(std::atomic<float>& pitchRatio, double sampleRate) const
    {
        return std::make_unique<Engine>(pitchRatio, sampleRate);
    }

    AnalysisPtr Factory::createAnalysis(int freqPerBin) const
    {
        return std::make_unique<Analysis>(freqPerBin);
    }

    SynthesisPtr Factory::createSynthesis(int freqPerBin, AnalysisPtr analysis) const
    {
        return std::make_unique<Synthesis>(freqPerBin, std::move(analysis));
    }
}
