# include <Siv3D.hpp>

void Main()
{
	const Font timerFont{ 200 }, taskFont{ 30 }, regularFont{ 50 };
	int set = 0, total = 0;
	String now = U"short breaks";
	Minutes pomodoro = 1min, shorBreaks = 5min, lognBreaks = 30min;
	Timer timer{ pomodoro, StartImmediately::No };
	String labelStr = U"Start";
	String text;
	constexpr Rect area{ 50,400,700,170 };
	const Audio audio{ U"audio/1.wav" };
	Color stopwatchColor = ColorF{ 0.0 };
	Scene::SetBackground(Palette::White);

	while (System::Update())
	{
		// How to use
		if (SimpleGUI::Button(U"How to use", Vec2{ 650, 10 }, unspecified))
		{
			System::LaunchBrowser(U"https://github.com/yashikota/pomodoro-timer#how-to-use");
		}

		if (labelStr.narrow().compare("Start") == 0)
		{
			// Timer start
			if (SimpleGUI::Button(labelStr, Vec2{ 650, 280 }, 100))
			{
				timer.start();
				stopwatchColor = ColorF{ 0.0 };
				labelStr = U"Pause";
			}
		}
		else
		{
			// Timer pause
			if (SimpleGUI::Button(labelStr, Vec2{ 650, 280 }, 100))
			{
				timer.pause();
				stopwatchColor = ColorF{ 1.0, 0.0, 0.0 };
				labelStr = U"Start";
				audio.stop();
			}
		}

		// Display timer
		timerFont(timer.format(U"mm:ss")).draw(40, 150, stopwatchColor);

		// Display now status
		regularFont(U"Now: {}"_fmt(now)).draw(50, 70, ColorF{0.0});

		// Display set and total
		regularFont(U"Set: {}"_fmt(set)).draw(50, 130, ColorF{ 0.0 });
		regularFont(U"Total: {}"_fmt(total)).draw(300, 130, ColorF{ 0.0 });
		
		// Play alarm
		if (timer.isRunning() && timer.min() == 0 && timer.s() == 0)
		{
			audio.play();
		}

		// Increment set
		if (timer.min() == 0 && timer.s() == 0)
		{
			set++;
		}

		// Increment total (four times set)
		if (set != 0 && set % 4 == 0)
		{
			total++;
		}
		
		// Input tasks
		TextInput::UpdateText(text);
		const String editingText = TextInput::GetEditingText();
		area.draw(ColorF{ 0.5, 0.5, 0.5 });
		taskFont(text + U'|' + editingText).draw(area.stretched(-20));
	}
}
