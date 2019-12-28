#pragma once
// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T>
void tnbLib::debug::controlSwitches<T>::operator=(const T& rhs)
{
	switchValue_ = rhs;
}


template<class T>
const T tnbLib::debug::controlSwitches<T>::operator&(const T& rhs)
{
	return switchValue_ & rhs;
}


// * * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * //

template<class T>
bool tnbLib::operator==
(
	const debug::controlSwitches<T>& lhs,
	const debug::controlSwitches<T>& rhs
	)
{
	return lhs() == rhs();
}


template<class T>
bool tnbLib::operator==
(
	const T& lhs,
	const debug::controlSwitches<T>& rhs
	)
{
	return lhs == rhs();
}


template<class T>
bool tnbLib::operator==
(
	const debug::controlSwitches<T>& lhs,
	const T& rhs
	)
{
	return lhs() == rhs;
}


template<class T>
bool tnbLib::operator!=
(
	const debug::controlSwitches<T>& lhs,
	const debug::controlSwitches<T>& rhs
	)
{
	return lhs() != rhs();
}


template<class T>
bool tnbLib::operator!=
(
	const T& lhs,
	const debug::controlSwitches<T>& rhs
	)
{
	return lhs != rhs();
}


template<class T>
bool tnbLib::operator!=
(
	const debug::controlSwitches<T>& lhs,
	const T& rhs
	)
{
	return lhs() != rhs;
}


template<class T>
bool tnbLib::operator>=
(
	const debug::controlSwitches<T>& lhs,
	const debug::controlSwitches<T>& rhs
	)
{
	return lhs() >= rhs();
}


template<class T>
bool tnbLib::operator>=
(
	const T& lhs,
	const debug::controlSwitches<T>& rhs
	)
{
	return lhs >= rhs();
}


template<class T>
bool tnbLib::operator>=
(
	const debug::controlSwitches<T>& lhs,
	const T& rhs
	)
{
	return lhs() >= rhs;
}


template<class T>
bool tnbLib::operator>
(
	const debug::controlSwitches<T>& lhs,
	const debug::controlSwitches<T>& rhs
	)
{
	return lhs() > rhs();
}


template<class T>
bool tnbLib::operator>
(
	const T& lhs,
	const debug::controlSwitches<T>& rhs
	)
{
	return lhs > rhs();
}


template<class T>
bool tnbLib::operator>
(
	const debug::controlSwitches<T>& lhs,
	const T& rhs
	)
{
	return lhs() > rhs;
}


template<class T>
bool tnbLib::operator<=
(
	const debug::controlSwitches<T>& lhs,
	const debug::controlSwitches<T>& rhs
	)
{
	return lhs() <= rhs();
}


template<class T>
bool tnbLib::operator<=
(
	const T& lhs,
	const debug::controlSwitches<T>& rhs
	)
{
	return lhs <= rhs();
}


template<class T>
bool tnbLib::operator<=
(
	const debug::controlSwitches<T>& lhs,
	const T& rhs
	)
{
	return lhs() <= rhs;
}


template<class T>
bool tnbLib::operator<
(
	const debug::controlSwitches<T>& lhs,
	const debug::controlSwitches<T>& rhs
	)
{
	return lhs() < rhs();
}


template<class T>
bool tnbLib::operator<
(
	const T& lhs,
	const debug::controlSwitches<T>& rhs
	)
{
	return lhs < rhs();
}


template<class T>
bool tnbLib::operator<
(
	const debug::controlSwitches<T>& lhs,
	const T& rhs
	)
{
	return lhs() < rhs;
}


// ************************************************************************* //