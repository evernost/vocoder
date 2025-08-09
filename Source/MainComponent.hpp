// ============================================================================
// Project        : chordScope
// Module name    : MainComponent
// File name      : MainComponent.hpp
// File type      : C++ 17
// Purpose        : app class definition (header)
// Author         : QuBi (nitrogenium@outlook.fr)
// Creation date  : August 5th, 2025
// ----------------------------------------------------------------------------
// Best viewed with space indentation (2 spaces)
// ============================================================================
#pragma once

// ============================================================================
// EXTERNALS
// ============================================================================
#include <JuceHeader.h>



// ============================================================================
// CLASS DEFINITION
// ============================================================================
class MainComponent : public juce::AudioAppComponent
{
  public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo&) override;
    void releaseResources() override;

    void resized() override;
    void paint(juce::Graphics& g) override;

  private:

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
