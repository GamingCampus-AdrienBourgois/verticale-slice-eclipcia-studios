#include "stdafx.h"
#include "Settings.hpp"

Settings::Settings(StateMachine& machine) 
	: State(machine)
{
	InitAssets();
	InitButtons();
	InitSeekerBars();
	InitSprites();
	InitTexts();
}

Settings::~Settings() {
	for (auto& s : m_SeekerBars)
		delete s.second;

	for (auto& p : m_pickers)
		delete p;
	
}

void Settings::FixedUpdate() {

}

void Settings::Update() {
	UpdateButtons();
	UpdateSeekerBars();
}

void Settings::Render(sf::RenderTarget& target) {
	auto& shader = ShaderLibrary::Get().GetShader("blur");
	shader.setUniform("u_blur_radius", 0.008f);

	for (const auto& s : m_Sprites)
		target.draw(s.second, &shader);

	for (const auto& b : m_Buttons)
		target.draw(b.second);

	for (const auto& s : m_SeekerBars)
		target.draw(*s.second);

	for (const auto& t : m_Texts)
		target.draw(t.second);

	for (const auto& p : m_pickers)
		target.draw(*p);
}

void Settings::InitTexts() {
	// TITLE
	{
		auto& t = m_Texts["sound"];
		t.setString("SOUND VOLUME");
		t.setCharacterSize(90);
	}

	{
		auto& t = m_Texts["music"];
		t.setString("MUSIC VOLUME");
		t.setCharacterSize(90);
	}

	{
		auto& t = m_Texts["player_particle"];
		t.setString("PLAYER PARTICLE");
		t.setCharacterSize(90);
	}

	{
		auto& t = m_Texts["primary"];
		t.setString("PRIMARY");
		t.setCharacterSize(40);
	}

	{
		auto& t = m_Texts["secondary"];
		t.setString("SECONDARY");
		t.setCharacterSize(40);
	}

	for (auto& t : m_Texts)
		t.second.setFont(m_FontManager.Get("default"));

	m_Texts["sound"].setPosition(sf::Vector2f(815.0f, 250.0f));
											  
	m_Texts["music"].setPosition(sf::Vector2f(815.0f, 500.0f));
}

void Settings::UpdateSeekerBars() {
	for (auto& s : m_SeekerBars)
		s.second->Update(GetMousePos());
}

void Settings::InitSeekerBars() {
	std::initializer_list<std::pair<const std::string, SeekerBar*>> init =
	{
		{ "sound", new SeekerBar(sf::Vector2f(350.0f, 350.0f), m_FontManager.Get("default"), 10, Extern::sound_volume / 8) },
		{ "music", new SeekerBar(sf::Vector2f(350.0f, 600.0f), m_FontManager.Get("default"), 10, Extern::music_volume / 8) },
	};

	m_SeekerBars = init;

	auto& soundVolume = Extern::sound_volume;

	m_SeekerBars["sound"]->SetLeftFunction([&soundVolume]() {
		if (soundVolume > 0)
			soundVolume -= 8;
	});

	m_SeekerBars["sound"]->SetRightFunction([&soundVolume]() {
		if (soundVolume < 80)
			soundVolume += 8;
	});

	auto& musicVolume = Extern::music_volume;

	m_SeekerBars["music"]->SetLeftFunction([&musicVolume]() {
		if (musicVolume > 0)
			musicVolume -= 8;
	});

	m_SeekerBars["music"]->SetRightFunction([&musicVolume]() {
		if (musicVolume < 80)
			musicVolume += 8;
	});
}

void Settings::InitSprites() {
	{
		auto& s = m_Sprites["background"];
		s.setTexture(m_TextureManager.Get("background"));
	}
}

void Settings::UpdateButtons() {
	for (auto& b : m_Buttons)
		b.second.Update(GetMousePos());
}

void Settings::InitButtons() {
	std::initializer_list<std::pair<const std::string, Button>> init =
	{
		{ "back", Button("BACK", sf::Vector2f(180.0f, 80.0f), m_FontManager.Get("default")) },
	};

	m_Buttons = init;

	auto& transition = Transition::Get();

	m_Buttons["back"].SetFunction([&]() {
		transition.SetFunction([&]() {
			i_isRunning = false; 
			transition.Start(Mode::Unveil);
		});
		transition.Start(Mode::Veil);
	});
}

void Settings::InitAssets() {
	//TEXTURES//
	{
		m_TextureManager.Load("background", "res/textures/menu.png");
	}
	//FONTS//
	{
		m_FontManager.Load("default", "res/fonts/upheavtt.ttf");
	}
}
