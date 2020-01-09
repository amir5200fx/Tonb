#include <processorLduInterface.hxx>

#include <IPstream.hxx>
#include <OPstream.hxx>

// * * * * * * * * * * * * * * * Member Functions * * *  * * * * * * * * * * //

template<class Type>
void tnbLib::processorLduInterface::send
(
	const Pstream::commsTypes commsType,
	const UList<Type>& f
) const
{
	if (commsType == Pstream::blocking || commsType == Pstream::scheduled)
	{
		OPstream::write
		(
			commsType,
			neighbProcNo(),
			reinterpret_cast<const char*>(f.begin()),
			f.byteSize()
		);
	}
	else if (commsType == Pstream::nonBlocking)
	{
		resizeBuf(receiveBuf_, f.size() * sizeof(Type));

		IPstream::read
		(
			commsType,
			neighbProcNo(),
			receiveBuf_.begin(),
			receiveBuf_.size()
		);

		resizeBuf(sendBuf_, f.byteSize());
		memcpy(sendBuf_.begin(), f.begin(), f.byteSize());

		OPstream::write
		(
			commsType,
			neighbProcNo(),
			sendBuf_.begin(),
			f.byteSize()
		);
	}
	else
	{
		FatalErrorIn("processorLduInterface::send")
			<< "Unsupported communications type " << commsType
			<< exit(FatalError);
	}
}


template<class Type>
void tnbLib::processorLduInterface::receive
(
	const Pstream::commsTypes commsType,
	UList<Type>& f
) const
{
	if (commsType == Pstream::blocking || commsType == Pstream::scheduled)
	{
		IPstream::read
		(
			commsType,
			neighbProcNo(),
			reinterpret_cast<char*>(f.begin()),
			f.byteSize()
		);
	}
	else if (commsType == Pstream::nonBlocking)
	{
		memcpy(f.begin(), receiveBuf_.begin(), f.byteSize());
	}
	else
	{
		FatalErrorIn("processorLduInterface::receive")
			<< "Unsupported communications type " << commsType
			<< exit(FatalError);
	}
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type> > tnbLib::processorLduInterface::receive
(
	const Pstream::commsTypes commsType,
	const label size
) const
{
	tmp<Field<Type> > tf(new Field<Type>(size));
	receive(commsType, tf());
	return tf;
}


template<class Type>
void tnbLib::processorLduInterface::compressedSend
(
	const Pstream::commsTypes commsType,
	const UList<Type>& f
) const
{
	if (sizeof(scalar) != sizeof(float) && f.size())
	{
		static const label nCmpts = sizeof(Type) / sizeof(scalar);
		label nm1 = (f.size() - 1)*nCmpts;
		label nlast = sizeof(Type) / sizeof(float);
		label nFloats = nm1 + nlast;
		label nBytes = nFloats * sizeof(float);

		const scalar *sArray = reinterpret_cast<const scalar*>(f.begin());
		const scalar *slast = &sArray[nm1];
		resizeBuf(sendBuf_, nBytes);
		float *fArray = reinterpret_cast<float*>(sendBuf_.begin());

		for (register label i = 0; i < nm1; i++)
		{
			fArray[i] = sArray[i] - slast[i%nCmpts];
		}

		reinterpret_cast<Type&>(fArray[nm1]) = f[f.size() - 1];

		if (commsType == Pstream::blocking || commsType == Pstream::scheduled)
		{
			OPstream::write
			(
				commsType,
				neighbProcNo(),
				sendBuf_.begin(),
				nBytes
			);
		}
		else if (commsType == Pstream::nonBlocking)
		{
			resizeBuf(receiveBuf_, nBytes);

			IPstream::read
			(
				commsType,
				neighbProcNo(),
				receiveBuf_.begin(),
				receiveBuf_.size()
			);

			OPstream::write
			(
				commsType,
				neighbProcNo(),
				sendBuf_.begin(),
				nBytes
			);
		}
		else
		{
			FatalErrorIn("processorLduInterface::compressedSend")
				<< "Unsupported communications type " << commsType
				<< exit(FatalError);
		}
	}
	else
	{
		this->send(commsType, f);
	}
}

template<class Type>
void tnbLib::processorLduInterface::compressedReceive
(
	const Pstream::commsTypes commsType,
	UList<Type>& f
) const
{
	if (sizeof(scalar) != sizeof(float) && f.size())
	{
		static const label nCmpts = sizeof(Type) / sizeof(scalar);
		label nm1 = (f.size() - 1)*nCmpts;
		label nlast = sizeof(Type) / sizeof(float);
		label nFloats = nm1 + nlast;
		label nBytes = nFloats * sizeof(float);

		if (commsType == Pstream::blocking || commsType == Pstream::scheduled)
		{
			resizeBuf(receiveBuf_, nBytes);

			IPstream::read
			(
				commsType,
				neighbProcNo(),
				receiveBuf_.begin(),
				nBytes
			);
		}
		else if (commsType != Pstream::nonBlocking)
		{
			FatalErrorIn("processorLduInterface::compressedReceive")
				<< "Unsupported communications type " << commsType
				<< exit(FatalError);
		}

		const float *fArray =
			reinterpret_cast<const float*>(receiveBuf_.begin());
		f[f.size() - 1] = reinterpret_cast<const Type&>(fArray[nm1]);
		scalar *sArray = reinterpret_cast<scalar*>(f.begin());
		const scalar *slast = &sArray[nm1];

		for (register label i = 0; i < nm1; i++)
		{
			sArray[i] = fArray[i] + slast[i%nCmpts];
		}
	}
	else
	{
		this->receive<Type>(commsType, f);
	}
}

template<class Type>
tnbLib::tmp<tnbLib::Field<Type> > tnbLib::processorLduInterface::compressedReceive
(
	const Pstream::commsTypes commsType,
	const label size
) const
{
	tmp<Field<Type> > tf(new Field<Type>(size));
	compressedReceive(commsType, tf());
	return tf;
}


// ************************************************************************* //