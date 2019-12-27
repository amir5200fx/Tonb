#include <IPstream.hxx>
#include <OPstream.hxx>
#include <contiguous.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template <class T>
	void Pstream::gatherList
	(
		const List<Pstream::commsStruct>& comms,
		List<T>& Values
	)
	{
		if (Pstream::parRun())
		{
			if (Values.size() != Pstream::nProcs())
			{
				FatalErrorIn
				(
					"Pstream::gatherList(const List<Pstream::commsStruct>&"
					", List<T>)"
				) << "Size of list:" << Values.size()
					<< " does not equal the number of processors:"
					<< Pstream::nProcs()
					<< tnbLib::abort(FatalError);
			}

			// Get my communication order
			const commsStruct& myComm = comms[Pstream::myProcNo()];

			// Receive from my downstairs neighbours
			forAll(myComm.below(), belowI)
			{
				label belowID = myComm.below()[belowI];
				const labelList& belowLeaves = comms[belowID].allBelow();

				if (contiguous<T>())
				{
					List<T> receivedValues(belowLeaves.size() + 1);

					IPstream::read
					(
						Pstream::scheduled,
						belowID,
						reinterpret_cast<char*>(receivedValues.begin()),
						receivedValues.byteSize()
					);

					Values[belowID] = receivedValues[0];

					forAll(belowLeaves, leafI)
					{
						Values[belowLeaves[leafI]] = receivedValues[leafI + 1];
					}
				}
				else
				{
					IPstream fromBelow(Pstream::scheduled, belowID);
					fromBelow >> Values[belowID];

					if (debug > 1)
					{
						Pout << " received through "
							<< belowID << " data from:" << belowID
							<< " data:" << Values[belowID] << endl;
					}

					// Receive from all other processors below belowID
					forAll(belowLeaves, leafI)
					{
						label leafID = belowLeaves[leafI];
						fromBelow >> Values[leafID];

						if (debug > 1)
						{
							Pout << " received through "
								<< belowID << " data from:" << leafID
								<< " data:" << Values[leafID] << endl;
						}
					}
				}
			}

			// Send up from Values:
			// - my own value first
			// - all belowLeaves next
			if (myComm.above() != -1)
			{
				const labelList& belowLeaves = myComm.allBelow();

				if (debug > 1)
				{
					Pout << " sending to " << myComm.above()
						<< " data from: " << Pstream::myProcNo()
						<< " data: " << Values[Pstream::myProcNo()] << endl;
				}

				if (contiguous<T>())
				{
					List<T> sendingValues(belowLeaves.size() + 1);
					sendingValues[0] = Values[Pstream::myProcNo()];

					forAll(belowLeaves, leafI)
					{
						sendingValues[leafI + 1] = Values[belowLeaves[leafI]];
					}

					OPstream::write
					(
						Pstream::scheduled,
						myComm.above(),
						reinterpret_cast<const char*>(sendingValues.begin()),
						sendingValues.byteSize()
					);
				}
				else
				{
					OPstream toAbove(Pstream::scheduled, myComm.above());
					toAbove << Values[Pstream::myProcNo()];

					forAll(belowLeaves, leafI)
					{
						label leafID = belowLeaves[leafI];

						if (debug > 1)
						{
							Pout << " sending to "
								<< myComm.above() << " data from: " << leafID
								<< " data: " << Values[leafID] << endl;
						}
						toAbove << Values[leafID];
					}
				}
			}
		}
	}


	template <class T>
	void Pstream::gatherList(List<T>& Values)
	{
		if (Pstream::nProcs() < Pstream::nProcsSimpleSum())
		{
			gatherList(Pstream::linearCommunication(), Values);
		}
		else
		{
			gatherList(Pstream::treeCommunication(), Values);
		}
	}


	template <class T>
	void Pstream::scatterList
	(
		const List<Pstream::commsStruct>& comms,
		List<T>& Values
	)
	{
		if (Pstream::parRun())
		{
			if (Values.size() != Pstream::nProcs())
			{
				FatalErrorIn
				(
					"Pstream::scatterList(const List<Pstream::commsStruct>&"
					", List<T>)"
				) << "Size of list:" << Values.size()
					<< " does not equal the number of processors:"
					<< Pstream::nProcs()
					<< tnbLib::abort(FatalError);
			}

			// Get my communication order
			const commsStruct& myComm = comms[Pstream::myProcNo()];

			// Receive from up
			if (myComm.above() != -1)
			{
				const labelList& notBelowLeaves = myComm.allNotBelow();

				if (contiguous<T>())
				{
					List<T> receivedValues(notBelowLeaves.size());

					IPstream::read
					(
						Pstream::scheduled,
						myComm.above(),
						reinterpret_cast<char*>(receivedValues.begin()),
						receivedValues.byteSize()
					);

					forAll(notBelowLeaves, leafI)
					{
						Values[notBelowLeaves[leafI]] = receivedValues[leafI];
					}
				}
				else
				{
					IPstream fromAbove(Pstream::scheduled, myComm.above());

					forAll(notBelowLeaves, leafI)
					{
						label leafID = notBelowLeaves[leafI];
						fromAbove >> Values[leafID];

						if (debug)
						{
							Pout << " received through "
								<< myComm.above() << " data for:" << leafID
								<< " data:" << Values[leafID] << endl;
						}
					}
				}
			}

			// Send to my downstairs neighbours
			forAll(myComm.below(), belowI)
			{
				label belowID = myComm.below()[belowI];
				const labelList& notBelowLeaves = comms[belowID].allNotBelow();

				if (contiguous<T>())
				{
					List<T> sendingValues(notBelowLeaves.size());

					forAll(notBelowLeaves, leafI)
					{
						sendingValues[leafI] = Values[notBelowLeaves[leafI]];
					}

					OPstream::write
					(
						Pstream::scheduled,
						belowID,
						reinterpret_cast<const char*>(sendingValues.begin()),
						sendingValues.byteSize()
					);
				}
				else
				{
					OPstream toBelow(Pstream::scheduled, belowID);

					// Send data destined for all other processors below belowID
					forAll(notBelowLeaves, leafI)
					{
						label leafID = notBelowLeaves[leafI];
						toBelow << Values[leafID];

						if (debug)
						{
							Pout << " sent through "
								<< belowID << " data for:" << leafID
								<< " data:" << Values[leafID] << endl;
						}
					}
				}
			}
		}
	}


	template <class T>
	void Pstream::scatterList(List<T>& Values)
	{
		if (Pstream::nProcs() < Pstream::nProcsSimpleSum())
		{
			scatterList(Pstream::linearCommunication(), Values);
		}
		else
		{
			scatterList(Pstream::treeCommunication(), Values);
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //