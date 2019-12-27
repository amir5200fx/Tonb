#include <OPstream.hxx>
#include <IPstream.hxx>
#include <contiguous.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template <class T, class BinaryOp>
	void Pstream::gather
	(
		const List<Pstream::commsStruct>& comms,
		T& Value,
		const BinaryOp& bop
	)
	{
		if (Pstream::parRun())
		{
			// Get my communication order
			const commsStruct& myComm = comms[Pstream::myProcNo()];

			// Receive from my downstairs neighbours
			forAll(myComm.below(), belowI)
			{
				T value;

				if (contiguous<T>())
				{
					IPstream::read
					(
						Pstream::scheduled,
						myComm.below()[belowI],
						reinterpret_cast<char*>(&value),
						sizeof(T)
					);
				}
				else
				{
					IPstream fromBelow(Pstream::scheduled, myComm.below()[belowI]);
					fromBelow >> value;
				}

				Value = bop(Value, value);
			}

			// Send up Value
			if (myComm.above() != -1)
			{
				if (contiguous<T>())
				{
					OPstream::write
					(
						Pstream::scheduled,
						myComm.above(),
						reinterpret_cast<const char*>(&Value),
						sizeof(T)
					);
				}
				else
				{
					OPstream toAbove(Pstream::scheduled, myComm.above());
					toAbove << Value;
				}
			}
		}
	}


	template <class T, class BinaryOp>
	void Pstream::gather(T& Value, const BinaryOp& bop)
	{
		if (Pstream::nProcs() < Pstream::nProcsSimpleSum())
		{
			gather(Pstream::linearCommunication(), Value, bop);
		}
		else
		{
			gather(Pstream::treeCommunication(), Value, bop);
		}
	}


	template <class T>
	void Pstream::scatter(const List<Pstream::commsStruct>& comms, T& Value)
	{
		if (Pstream::parRun())
		{
			// Get my communication order
			const commsStruct& myComm = comms[Pstream::myProcNo()];

			// Receive from up
			if (myComm.above() != -1)
			{
				if (contiguous<T>())
				{
					IPstream::read
					(
						Pstream::scheduled,
						myComm.above(),
						reinterpret_cast<char*>(&Value),
						sizeof(T)
					);
				}
				else
				{
					IPstream fromAbove(Pstream::scheduled, myComm.above());
					fromAbove >> Value;
				}
			}

			// Send to my downstairs neighbours
			forAll(myComm.below(), belowI)
			{
				if (contiguous<T>())
				{
					OPstream::write
					(
						Pstream::scheduled,
						myComm.below()[belowI],
						reinterpret_cast<const char*>(&Value),
						sizeof(T)
					);
				}
				else
				{
					OPstream toBelow(Pstream::scheduled, myComm.below()[belowI]);
					toBelow << Value;
				}
			}
		}
	}


	template <class T>
	void Pstream::scatter(T& Value)
	{
		if (Pstream::nProcs() < Pstream::nProcsSimpleSum())
		{
			scatter(Pstream::linearCommunication(), Value);
		}
		else
		{
			scatter(Pstream::treeCommunication(), Value);
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //