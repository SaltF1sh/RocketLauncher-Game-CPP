#include "GameStateMachine.h"
#include "GameStateBase.h"
#include "GSPlay.h"

GameStateMachine::GameStateMachine()
{
	m_ActivesState = nullptr;
	m_NextState = nullptr;
}

GameStateMachine::~GameStateMachine()
{
	while (!m_StateStack.empty()) {
		delete m_StateStack.back();
		m_StateStack.pop_back();
	}
}

void GameStateMachine::ChangeState(GameStateBase* state)
{
	m_NextState = state;
}

void GameStateMachine::ChangeState(StateTypes st)
{
	printf("%d\n", (int)m_StateStack.size());
	GameStateBase* gs = GameStateBase::CreateState(st);
	ChangeState(gs);
}

void GameStateMachine::PushState(StateTypes st)
{
	GameStateBase* gs = GameStateBase::CreateState(st);
	if (!m_StateStack.empty()) {
		m_StateStack.back()->Pause();
	}
	m_NextState = gs;
	delete gs;
}

void GameStateMachine::PopState()
{
	if (!m_StateStack.empty()) {
		m_StateStack.back()->Exit();
		free(m_StateStack.back());
		m_StateStack.pop_back();
	}
	if (!m_StateStack.empty()) {
		m_StateStack.back()->Resume();
	}
	m_ActivesState = m_StateStack.back();
}

void GameStateMachine::PerformStateChange()
{
	if (m_NextState != nullptr) {
		if (!m_StateStack.empty()) {
			m_StateStack.back()->Exit();
		}
		m_StateStack.push_back(m_NextState);
		m_StateStack.back()->Init();
		m_ActivesState = m_NextState;
	}

	m_NextState = nullptr;
}

GameStateBase* GameStateMachine::currentState() const
{
	return m_ActivesState;
}

GameStateBase* GameStateMachine::nextState() const
{
	return m_NextState;
}

bool GameStateMachine::NeedToChangeState()
{
	return m_NextState != nullptr;
}

bool GameStateMachine::HasState()
{
	return m_StateStack.size() > 0;
}

void GameStateMachine::NewGame()
{
	GSPlay::numDeath = 0;
	GSPlay::curMap = 1;
	GSPlay::setCurMap(1);
}
