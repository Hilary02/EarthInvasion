#pragma once
enum anime {
	deadAnime,
	clearAnime
};

class IStageBase {
public:
	virtual void PlayAnimation(int type) = 0;
};