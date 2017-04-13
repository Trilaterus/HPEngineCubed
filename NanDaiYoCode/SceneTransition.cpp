#include "SceneTransition.h"

SceneTransition::SceneTransition()
{
}

void SceneTransition::setScenes(std::shared_ptr<Scene> prevScene, std::shared_ptr<Scene> nextScene)
{
	m_prevScene = prevScene;
	m_nextScene = nextScene;
}
