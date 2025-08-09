// ============================================================================
// Project        : vocoder
// Module name    : MainComponent
// File name      : MainComponent.cpp
// File type      : C++ 17
// Purpose        : app class definition
// Author         : QuBi (nitrogenium@outlook.fr)
// Creation date  : August 5th, 2025
// ----------------------------------------------------------------------------
// Best viewed with space indentation (2 spaces)
// ============================================================================

// ============================================================================
// EXTERNALS
// ============================================================================
#include "MainComponent.hpp"



// ----------------------------------------------------------------------------
// CLASS CONSTRUCTOR
// ----------------------------------------------------------------------------
MainComponent::MainComponent()
{
  setSize(600, 400);
  setAudioChannels(2, 2);
}



// ----------------------------------------------------------------------------
// CLASS DESTRUCTOR
// ----------------------------------------------------------------------------
MainComponent::~MainComponent()
{
  shutdownAudio();
}



// ----------------------------------------------------------------------------
// METHOD MainComponent::prepareToPlay()                            [INHERITED]
// ----------------------------------------------------------------------------
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
  juce::ignoreUnused(samplesPerBlockExpected, sampleRate);
}



// ----------------------------------------------------------------------------
// METHOD MainComponent::getNextAudioBlock()                        [INHERITED]
// ----------------------------------------------------------------------------
void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
  // auto* buffer = bufferToFill.buffer;

  // // Make sure to clear output channels beyond input channels
  // for (int channel = 0; channel < buffer->getNumChannels(); ++channel)
  // {
  //   auto* channelData = buffer->getWritePointer(channel, bufferToFill.startSample);
  //   // If your device has input channels, those input samples are already in the buffer’s read pointers.


  //   if (deviceManager.getCurrentAudioDevice()->getActiveInputChannels()[channel])
  //   {
  //     // For now, just copy input samples to output (pass through)
  //     // The input is already in the buffer at this point, so no separate input buffer is needed

  //     // If you want to process, do it here.
  //   }
  //   else
  //   {
  //     // No input on this channel, clear buffer to avoid noise
  //     juce::FloatVectorOperations::clear(channelData, bufferToFill.numSamples);
  //   }
  // }

  auto* device = deviceManager.getCurrentAudioDevice();
  auto inputChannels = device->getActiveInputChannels();
  auto outputChannels = device->getActiveOutputChannels();

  auto buffer = bufferToFill.buffer;

  // Pass through each channel
  for (int ch = 0; ch < buffer->getNumChannels(); ++ch)
  {
    if (inputChannels[ch] && outputChannels[ch])
    {
      auto* samples = buffer->getWritePointer(ch, bufferToFill.startSample);

      // Apply simple soft clipping distortion
      for (int i = 0; i < bufferToFill.numSamples; ++i)
      {
        float in = samples[i];       // mic input
        float drive = 2.5f;          // increase for more distortion
        float x = in * drive;

        // Soft clipping formula
        samples[i] = std::tanh(x);
      }
    }
    else
    {
      // No input for this channel → clear output to avoid noise
      buffer->clear(ch, bufferToFill.startSample, bufferToFill.numSamples);
    }
  }
}



// ----------------------------------------------------------------------------
// METHOD MainComponent::releaseResources()                         [INHERITED]
// ----------------------------------------------------------------------------
void MainComponent::releaseResources()
{
  // Free any allocated resources here
}



// ----------------------------------------------------------------------------
// METHOD MainComponent::paint()                                    [INHERITED]
// ----------------------------------------------------------------------------
void MainComponent::paint(juce::Graphics& g)
{
  g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

  g.setFont(juce::FontOptions(16.0f));
  g.setColour(juce::Colours::white);
  g.drawText("Vocoder App.", getLocalBounds(), juce::Justification::centred, true);
}



// ----------------------------------------------------------------------------
// METHOD MainComponent::resized()                                  [INHERITED]
// ----------------------------------------------------------------------------
void MainComponent::resized()
{
  // This is called when the MainComponent is resized.
  // If you add any child components, this is where you should
  // update their positions.
}


