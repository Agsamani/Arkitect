#pragma once
#include <unordered_map>

namespace Arkitect {
	template<typename S, typename T>
	class StateMachine {
	public:
		StateMachine();
		~StateMachine() = default;

		S& GetCurrentState() const { return m_CurrentState; }
		void SetCurrentState(const S& val) { m_CurrentState = val; }

		void AddTranstion(const S& from, const S& to, const T& transiton);
		void RemoveTranstion(const S& from, const T& transiton);

		// Maybe remove transition?

		void DoTransition(const T& transiton);

	private:
		std::unordered_map<S, std::unordered_map<T, S>> m_Machine;
		S m_CurrentState;
	};

	template<typename S, typename T>
	StateMachine<S, T>::StateMachine()
	{

	}

	template<typename S, typename T>
	void StateMachine<S, T>::AddTranstion(const S& from, const S& to, const T& transiton)
	{
		m_Machine[from][transiton] = to;
	}

	template<typename S, typename T>
	void StateMachine<S, T>::RemoveTranstion(const S& from, const T& transiton)
	{
		m_Machine[from].erase(transiton);
	}

	template<typename S, typename T>
	void StateMachine<S, T>::DoTransition(const T& transiton)
	{
		if (m_Machine[m_CurrentState].count(transiton) == 1) { // What if current state is not in the map?
			m_CurrentState = (m_Machine[m_CurrentState][transiton]);
		}
	}

}
