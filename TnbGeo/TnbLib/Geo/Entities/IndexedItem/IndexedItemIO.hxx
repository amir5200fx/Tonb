#pragma once
namespace tnbLib
{

	template<class T>
	void IndexedItem<T>::save(TNB_oARCH_TYPE & ar, const unsigned int version) const
	{
		ar << Index();
		ar << Item();
	}

	template<class T>
	void IndexedItem<T>::load(TNB_iARCH_TYPE & ar, const unsigned int version)
	{
		Standard_Integer id;
		T item;

		ar >> id;
		ar >> item;

		SetIndex(id);
		SetItem(std::move(item));
	}
}