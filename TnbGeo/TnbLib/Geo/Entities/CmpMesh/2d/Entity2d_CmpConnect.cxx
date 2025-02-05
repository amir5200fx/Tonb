#include <Entity2d_CmpConnect.hxx>

std::shared_ptr<tnbLib::Entity2d_CmpConnect> tnbLib::Entity2d_CmpConnect::Reversed() const
{
	auto copy = Copy();
	copy->Reverse();
	return copy;
}
