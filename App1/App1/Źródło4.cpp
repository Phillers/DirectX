// Include the precompiled headers
#include "pch.h"
#include "Game.h"

// Use some common namespaces to simplify the code
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Popups;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace Platform;


// the class definition for the core "framework" of our app
ref class App sealed : public IFrameworkView
{
	bool WindowClosed;    // change to true when it's time to close the window
	CGame Game;
public:
	virtual void Initialize(CoreApplicationView^ AppView)
	{
		AppView->Activated += ref new TypedEventHandler
			<CoreApplicationView^, IActivatedEventArgs^>(this, &App::OnActivated);

		WindowClosed = false;    // initialize to false
	}
	virtual void SetWindow(CoreWindow^ Window)
	{
		Window->Closed += ref new TypedEventHandler
			<CoreWindow^, CoreWindowEventArgs^>(this, &App::Closed);
		Window->PointerPressed += ref new TypedEventHandler
			<CoreWindow^, PointerEventArgs^>(this, &App::PointerPressed);
	}
	virtual void Load(String^ EntryPoint) {}
	virtual void Run()
	{
		Game.Initialize();

		CoreWindow^ Window = CoreWindow::GetForCurrentThread();

		// repeat until window closes
		while (!WindowClosed)
		{
			Window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

			// Run game code here
			Game.Update();
			Game.Render();
		}
	}
	virtual void Uninitialize() {}

	void OnActivated(CoreApplicationView^ CoreAppView, IActivatedEventArgs^ Args)
	{
		CoreWindow^ Window = CoreWindow::GetForCurrentThread();
		Window->Activate();
	}

	void Closed(CoreWindow^ sender, CoreWindowEventArgs^ args)
	{
		WindowClosed = true;    // Time to end the endless loop
	}
	void PointerPressed(CoreWindow^ Window, PointerEventArgs^ Args)
	{
		float color[4] = {Args->CurrentPoint->Position.X/1000.0, 1, Args->CurrentPoint->Position.Y/1000.0, 1};
		Game.SetColor(color);
	}
};


// the class definition that creates an instance of our core framework class
ref class AppSource sealed : IFrameworkViewSource
{
public:
	virtual IFrameworkView^ CreateView()
	{
		return ref new App();    // create an App class and return it
	}
};

[MTAThread]    // define main() as a multi-threaded-apartment function

// the starting point of all programs
int main(Array<String^>^ args)
{
	CoreApplication::Run(ref new AppSource());    // create and run a new AppSource class
	return 0;
}
