#include <Marine_Origin.hxx>

#include <gp.hxx>

const gp_Ax2 & tnbLib::Marine_Origin::Origin()
{
	return gp::XOY();
}