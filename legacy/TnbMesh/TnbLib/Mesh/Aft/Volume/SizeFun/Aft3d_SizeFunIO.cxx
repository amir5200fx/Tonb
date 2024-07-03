#include <Aft3d_SizeFun.hxx>

#include <Entity3d_Box.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::legLib::Aft3d_SizeFun)
{
	ar& theDomain_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::legLib::Aft3d_SizeFun)
{
	ar& theDomain_;
}