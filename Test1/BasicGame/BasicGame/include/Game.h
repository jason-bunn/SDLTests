#ifndef GAME_H
#define GAME_H

class Game{
private:
	bool			exitGame;
public:
					Game();
					~Game();

	bool			Init();
	void			Run();
	void			Update();
	void			Render();
	void			ProcessEvents();
	void			ProcessInput();
	void			CleanupResources();
};

#endif