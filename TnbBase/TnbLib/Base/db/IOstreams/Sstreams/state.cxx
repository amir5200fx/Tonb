//#include <token.hxx>
//#include <int.hxx>
//#include <error.hxx>
//#include <OSstream.hxx>
//
//// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
////  Print state of ostream.
//
//void tnbLib::state(ostream& to, const string& s)
//{
//	state_value osState = state_value(to.rdstate());
//
//	switch (osState)
//	{
//	case _good:                // Do not anything 'unusual'.
//		break;
//
//	case _eof:
//		Info
//			<< "Output stream: premature end of stream", s << endl;
//		break;
//
//	case _fail:
//		SeriousErrorIn("state(ostream& to, const string& s)")
//			<< "Output stream failure (bad format?)", s << endl;
//		break;
//
//	case (_fail + _eof):
//		SeriousErrorIn("state(ostream& to, const string& s)")
//			<< "Output stream failure and end of stream", s << endl;
//		break;
//
//	case _bad:
//		SeriousErrorIn("state(ostream& to, const string& s)")
//			<< "Serious output stream failure", s << endl;
//		break;
//
//	default:
//		SeriousErrorIn("state(ostream& to, const string& s)")
//			<< "Output stream failure of unknown type", s << endl
//			<< "Stream state value = ", osState << endl;
//		break;
//	}
//
//	return;
//}
//
//
////  Print state of istream.
//void tnbLib::state(istream& from, const string& s)
//{
//	state_value isState = state_value(from.rdstate());
//
//	switch (isState)
//	{
//	case _good:                // Do not anything 'unusual'.
//		break;
//
//	case _eof:
//		Info
//			<< "Input stream: premature end of stream", s << endl;
//		Info << "If all else well, possibly a quote mark missing" << endl;
//		break;
//
//	case _fail:
//		SeriousErrorIn("state(istream& from, const string& s)")
//			<< "Input stream failure (bad format?)", s << endl;
//		Info << "If all else well, possibly a quote mark missing" << endl;
//		break;
//
//	case (_fail + _eof):
//		SeriousErrorIn("state(istream& from, const string& s)")
//			<< "Input stream failure and end of stream", s << endl;
//		Info << "If all else well, possibly a quote mark missing" << endl;
//		break;
//
//	case _bad:
//		SeriousErrorIn("state(istream& from, const string& s)")
//			<< "Serious input stream failure", s << endl;
//		break;
//
//	default:
//		SeriousErrorIn("state(istream& from, const string& s)")
//			<< "Input stream failure of unknown type", s << endl;
//		SeriousErrorIn("state(istream& from, const string& s)")
//			<< "Stream state value = ", isState << endl;
//		break;
//	}
//
//	return;
//}
//
//
//// ************************************************************************* //