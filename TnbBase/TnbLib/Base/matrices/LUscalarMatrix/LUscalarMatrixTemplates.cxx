#include <LUscalarMatrix.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::LUscalarMatrix::solve(Field<Type>& sourceSol) const
{
	if (Pstream::parRun())
	{
		Field<Type> completeSourceSol(n());

		if (Pstream::master())
		{
			typename Field<Type>::subField
			(
				completeSourceSol,
				sourceSol.size()
			).assign(sourceSol);

			for
				(
					int slave = Pstream::firstSlave();
					slave <= Pstream::lastSlave();
					slave++
					)
			{
				IPstream::read
				(
					Pstream::scheduled,
					slave,
					reinterpret_cast<char*>
					(
						&(completeSourceSol[procOffsets_[slave]])
						),
						(procOffsets_[slave + 1] - procOffsets_[slave]) * sizeof(Type)
				);
			}
		}
		else
		{
			OPstream::write
			(
				Pstream::scheduled,
				Pstream::masterNo(),
				reinterpret_cast<const char*>(sourceSol.begin()),
				sourceSol.byteSize()
			);
		}

		if (Pstream::master())
		{
			LUBacksubstitute(*this, pivotIndices_, completeSourceSol);

			sourceSol = typename Field<Type>::subField
			(
				completeSourceSol,
				sourceSol.size()
			);

			for
				(
					int slave = Pstream::firstSlave();
					slave <= Pstream::lastSlave();
					slave++
					)
			{
				OPstream::write
				(
					Pstream::blocking,
					slave,
					reinterpret_cast<const char*>
					(
						&(completeSourceSol[procOffsets_[slave]])
						),
						(procOffsets_[slave + 1] - procOffsets_[slave]) * sizeof(Type)
				);
			}
		}
		else
		{
			IPstream::read
			(
				Pstream::blocking,
				Pstream::masterNo(),
				reinterpret_cast<char*>(sourceSol.begin()),
				sourceSol.byteSize()
			);
		}
	}
	else
	{
		LUBacksubstitute(*this, pivotIndices_, sourceSol);
	}
}


// ************************************************************************* //
