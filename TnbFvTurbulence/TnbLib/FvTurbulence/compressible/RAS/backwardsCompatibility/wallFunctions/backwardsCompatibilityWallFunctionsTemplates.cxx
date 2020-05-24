#include <backwardsCompatibilityWallFunctions.hxx>

#include <tnbTime.hxx>
#include <OSspecific.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace compressible
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type, class PatchType>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			autoCreateWallFunctionField
			(
				const word& fieldName,
				const fvMesh& mesh,
				const objectRegistry& obj
			)
		{
			IOobject mutHeader
			(
				"mut",
				mesh.time().timeName(),
				obj,
				IOobject::MUST_READ
			);

			typedef GeometricField<Type, fvPatchField, volMesh> fieldType;

			if (mutHeader.headerOk())
			{
				return tmp<fieldType>
					(
						new fieldType
						(
							IOobject
							(
								fieldName,
								mesh.time().timeName(),
								obj,
								IOobject::MUST_READ,
								IOobject::NO_WRITE,
								false
							),
							mesh
						)
						);
			}
			else
			{
				Info << "--> Upgrading " << fieldName
					<< " to employ run-time selectable wall functions" << endl;

				// Read existing field
				IOobject ioObj
				(
					fieldName,
					mesh.time().timeName(),
					obj,
					IOobject::MUST_READ,
					IOobject::NO_WRITE,
					false
				);

				tmp<fieldType> fieldOrig
				(
					new fieldType
					(
						ioObj,
						mesh
					)
				);

				// rename file
				Info << "    Backup original " << fieldName << " to "
					<< fieldName << ".old" << endl;
				mvBak(ioObj.objectPath(), "old");


				PtrList<fvPatchField<Type> > newPatchFields(mesh.boundary().size());

				forAll(newPatchFields, patchI)
				{
					if (mesh.boundary()[patchI].isWall())
					{
						newPatchFields.set
						(
							patchI,
							new PatchType
							(
								mesh.boundary()[patchI],
								fieldOrig().dimensionedInternalField()
							)
						);
						newPatchFields[patchI] == fieldOrig().boundaryField()[patchI];
					}
					else
					{
						newPatchFields.set
						(
							patchI,
							fieldOrig().boundaryField()[patchI].clone()
						);
					}
				}

				tmp<fieldType> fieldNew
				(
					new fieldType
					(
						IOobject
						(
							fieldName,
							mesh.time().timeName(),
							obj,
							IOobject::NO_READ,
							IOobject::NO_WRITE,
							false
						),
						mesh,
						fieldOrig().dimensions(),
						fieldOrig().internalField(),
						newPatchFields
					)
				);

				Info << "    Writing updated " << fieldName << endl;
				fieldNew().write();

				return fieldNew;
			}
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace compressible
} // End namespace tnbLib

// ************************************************************************* //