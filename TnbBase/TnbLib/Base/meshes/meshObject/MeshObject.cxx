#include <MeshObject.hxx>

#include <objectRegistry.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Mesh, class Type>
tnbLib::MeshObject<Mesh, Type>::MeshObject(const Mesh& mesh)
	:
	regIOobject
	(
		IOobject
		(
			Type::typeName,
			mesh.thisDb().instance(),
			mesh.thisDb()
		)
	),
	mesh_(mesh)
{
	if (Mesh::debug)
	{
		InfoIn("MeshObject<Mesh, Type>::MeshObject(const Mesh& mesh)")
			<< "Creating meshObject for type " << Type::typeName << endl;
	}
}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

template<class Mesh, class Type>
const Type& tnbLib::MeshObject<Mesh, Type>::New
(
	const Mesh& mesh
)
{
	if (!mesh.thisDb().objectRegistry::template foundObject<Type>(Type::typeName))
	{
		return store(new Type(mesh));
	}
	else
	{
		return mesh.thisDb().objectRegistry::template lookupObject<Type>
			(
				Type::typeName
				);
	}
}


template<class Mesh, class Type>
template<class Data1>
const Type& tnbLib::MeshObject<Mesh, Type>::New
(
	const Mesh& mesh,
	const Data1& d
)
{
	if (!mesh.thisDb().objectRegistry::template foundObject<Type>(Type::typeName))
	{
		return store(new Type(mesh, d));
	}
	else
	{
		return mesh.thisDb().objectRegistry::template lookupObject<Type>
			(
				Type::typeName
				);
	}
}


template<class Mesh, class Type>
template<class Data1, class Data2>
const Type& tnbLib::MeshObject<Mesh, Type>::New
(
	const Mesh& mesh,
	const Data1& d1,
	const Data2& d2
)
{
	if (!mesh.thisDb().objectRegistry::template foundObject<Type>(Type::typeName))
	{
		return store(new Type(mesh, d1, d2));
	}
	else
	{
		return mesh.thisDb().objectRegistry::template lookupObject<Type>
			(
				Type::typeName
				);
	}
}


template<class Mesh, class Type>
template<class Data1, class Data2, class Data3>
const Type& tnbLib::MeshObject<Mesh, Type>::New
(
	const Mesh& mesh,
	const Data1& d1,
	const Data2& d2,
	const Data3& d3
)
{
	if (!mesh.thisDb().objectRegistry::template foundObject<Type>(Type::typeName))
	{
		return store(new Type(mesh, d1, d2, d3));
	}
	else
	{
		return mesh.thisDb().objectRegistry::template lookupObject<Type>
			(
				Type::typeName
				);
	}
}


template<class Mesh, class Type>
template<class Data1, class Data2, class Data3, class Data4>
const Type& tnbLib::MeshObject<Mesh, Type>::New
(
	const Mesh& mesh,
	const Data1& d1,
	const Data2& d2,
	const Data3& d3,
	const Data4& d4
)
{
	if (!mesh.thisDb().objectRegistry::template foundObject<Type>(Type::typeName))
	{
		return store(new Type(mesh, d1, d2, d3, d4));
	}
	else
	{
		return mesh.thisDb().objectRegistry::template lookupObject<Type>
			(
				Type::typeName
				);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class Mesh, class Type>
bool tnbLib::MeshObject<Mesh, Type>::Delete(const Mesh& mesh)
{
	if (mesh.thisDb().objectRegistry::template foundObject<Type>(Type::typeName))
	{
		return mesh.thisDb().checkOut
		(
			const_cast<Type&>
			(
				mesh.thisDb().objectRegistry::template lookupObject<Type>
				(
					Type::typeName
					)
				)
		);
	}
	else
	{
		return false;
	}
}


template<class Mesh, class Type>
tnbLib::MeshObject<Mesh, Type>::~MeshObject()
{
	release();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Mesh, class Type>
bool tnbLib::MeshObject<Mesh, Type>::deleteObject() const
{
	return mesh().thisDb().checkOut
	(
		const_cast<MeshObject<Mesh, Type>&>(*this)
	);
}



// ************************************************************************* //
