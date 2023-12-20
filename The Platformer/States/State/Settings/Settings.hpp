#pragma once
#include "../States/Machine/State_Machine.hpp"

#include "../UI/Button.hpp"
#include "../UI/Seeker_Bar.hpp"
#include "../UI/Color_Picker.hpp"
#include "../Effects/Transition/Transition.hpp"

#include "../Effects/Particle Emitter/Particle_Emitter.hpp"

class Settings : public State {
public:
	Settings(StateMachine& machine);
	~Settings();

	virtual void FixedUpdate();
	virtual void Update();
	virtual void Render(sf::RenderTarget& target);

private:
	AssetManager<sf::Texture> m_TextureManager;
	AssetManager<sf::Font> m_FontManager;

	std::unordered_map<std::string, Button> m_Buttons;
	
	std::unordered_map<std::string, SeekerBar*> m_SeekerBars;
	std::unordered_map<std::string, sf::Sprite> m_Sprites;

	std::unordered_map<std::string, Text> m_Texts;
	std::vector<ColorPicker*> m_pickers;

	ParticleEmitter* m_emitter;

	void UpdateColorPickers();
	void InitColorPickers();

	void UpdateParticleEmitter();
	void InitParticleEmitter();

	void InitTexts();

	void UpdateSeekerBars();
	void InitSeekerBars();

	void InitSprites();

	void UpdateButtons();
	void InitButtons();

	void InitAssets();
};