// ============================================================================
// Project        : vocoder
// Module name    : Main
// File name      : Main.cpp
// File type      : C++ 17
// Purpose        : application entry point
// Author         : QuBi (nitrogenium@outlook.fr)
// Creation date  : August 9th, 2025
// ----------------------------------------------------------------------------
// Best viewed with space indentation (2 spaces)
// ============================================================================

// ============================================================================
// EXTERNALS
// ============================================================================
#include <JuceHeader.h>
#include "MainComponent.hpp"



// ----------------------------------------------------------------------------
// CLASS DEFINITION
// ----------------------------------------------------------------------------
class Vocoder : public juce::JUCEApplication
{
  public:
    const juce::String getApplicationName() override       { return "Vocoder"; }
    const juce::String getApplicationVersion() override    { return "1.0"; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    void initialise (const juce::String&) override
    {
      mainWindow.reset (new MainWindow (getApplicationName()));
    }

    void shutdown() override
    {
      mainWindow = nullptr;
    }

    void systemRequestedQuit() override
    {
      quit();
    }

    void anotherInstanceStarted (const juce::String&) override
    {
    }

    class MainWindow : public juce::DocumentWindow
    {
    public:
      MainWindow (juce::String name) : DocumentWindow(
        name,
        juce::Desktop::getInstance().getDefaultLookAndFeel()
        .findColour(ResizableWindow::backgroundColourId),
        DocumentWindow::allButtons)
      {
        setUsingNativeTitleBar(true);
        setContentOwned(new MainComponent(), true);
        setResizable(true, true);
        centreWithSize(getWidth(), getHeight());
        setVisible(true);
      }

      void closeButtonPressed() override
      {
        JUCEApplication::getInstance()->systemRequestedQuit();
      }
    };

  private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION (Vocoder)
