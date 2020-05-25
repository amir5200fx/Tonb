#include <symmTensorField.hxx>

#include <transformField.hxx>
#include <boolList.hxx>

#define TEMPLATE
#include <FieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

	void sqr(Field<symmTensor>& res, const UList<vector>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::sqr, vector, f)
	} 
	tmp<Field<symmTensor>> sqr(const UList<vector>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size())); sqr(tRes(), f); return tRes;
	} 
	tmp<Field<symmTensor>> sqr(const tmp<Field<vector>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, vector>::New(tf); sqr(tRes(), tf()); reuseTmp<symmTensor, vector>::clear(tf); return tRes;
	}
		
	void innerSqr(Field<symmTensor>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::innerSqr, symmTensor, f)
	} 
	tmp<Field<symmTensor>> innerSqr(const UList<symmTensor>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size())); innerSqr(tRes(), f); return tRes;
	} 
	tmp<Field<symmTensor>> innerSqr(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, symmTensor>::New(tf); innerSqr(tRes(), tf()); reuseTmp<symmTensor, symmTensor>::clear(tf); return tRes;
	}

		
	void tr(Field<scalar>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::tr, symmTensor, f)
	} 
	tmp<Field<scalar>> tr(const UList<symmTensor>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size())); tr(tRes(), f); return tRes;
	} 
	tmp<Field<scalar>> tr(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, symmTensor>::New(tf); tr(tRes(), tf()); reuseTmp<scalar, symmTensor>::clear(tf); return tRes;
	}
		
	void sph(Field<sphericalTensor>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor, res, =, ::tnbLib::sph, symmTensor, f)
	} 
	tmp<Field<sphericalTensor>> sph(const UList<symmTensor>& f)
	{
		tmp<Field<sphericalTensor>> tRes(new Field<sphericalTensor>(f.size())); sph(tRes(), f); return tRes;
	} 
	tmp<Field<sphericalTensor>> sph(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<sphericalTensor>> tRes = reuseTmp<sphericalTensor, symmTensor>::New(tf); sph(tRes(), tf()); reuseTmp<sphericalTensor, symmTensor>::clear(tf); return tRes;
	}
		
	void symm(Field<symmTensor>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::symm, symmTensor, f)
	} 
	tmp<Field<symmTensor>> symm(const UList<symmTensor>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size())); symm(tRes(), f); return tRes;
	} 
	tmp<Field<symmTensor>> symm(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, symmTensor>::New(tf); symm(tRes(), tf()); reuseTmp<symmTensor, symmTensor>::clear(tf); return tRes;
	}
		
	void twoSymm(Field<symmTensor>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::twoSymm, symmTensor, f)
	} 
	tmp<Field<symmTensor>> twoSymm(const UList<symmTensor>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size())); twoSymm(tRes(), f); return tRes;
	} 
	tmp<Field<symmTensor>> twoSymm(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, symmTensor>::New(tf); twoSymm(tRes(), tf()); reuseTmp<symmTensor, symmTensor>::clear(tf); return tRes;
	}
		
	void dev(Field<symmTensor>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::dev, symmTensor, f)
	} 
	tmp<Field<symmTensor>> dev(const UList<symmTensor>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size())); dev(tRes(), f); return tRes;
	} 
	tmp<Field<symmTensor>> dev(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, symmTensor>::New(tf); dev(tRes(), tf()); reuseTmp<symmTensor, symmTensor>::clear(tf); return tRes;
	}
		
	void dev2(Field<symmTensor>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::dev2, symmTensor, f)
	} 
	tmp<Field<symmTensor>> dev2(const UList<symmTensor>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size())); dev2(tRes(), f); return tRes;
	} 
	tmp<Field<symmTensor>> dev2(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, symmTensor>::New(tf); dev2(tRes(), tf()); reuseTmp<symmTensor, symmTensor>::clear(tf); return tRes;
	}
		
	void det(Field<scalar>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::det, symmTensor, f)
	} 
	tmp<Field<scalar>> det(const UList<symmTensor>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size())); det(tRes(), f); return tRes;
	} 
	tmp<Field<scalar>> det(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, symmTensor>::New(tf); det(tRes(), tf()); reuseTmp<scalar, symmTensor>::clear(tf); return tRes;
	}
		
	void cof(Field<symmTensor>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::cof, symmTensor, f)
	} 
	tmp<Field<symmTensor>> cof(const UList<symmTensor>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size())); cof(tRes(), f); return tRes;
	} 
	tmp<Field<symmTensor>> cof(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, symmTensor>::New(tf); cof(tRes(), tf()); reuseTmp<symmTensor, symmTensor>::clear(tf); return tRes;
	}

	void hinv(Field<symmTensor>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::hinv, symmTensor, f)
	} 
	tmp<Field<symmTensor>> hinv(const UList<symmTensor>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size())); hinv(tRes(), f); return tRes;
	} 
	tmp<Field<symmTensor>> hinv(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, symmTensor>::New(tf); hinv(tRes(), tf()); reuseTmp<symmTensor, symmTensor>::clear(tf); return tRes;
	}

		// This is a nasty hack for flat geometries.  For serious SVD, please use hinv
		// (Singular value decomposition and Householder transfromations)
		// HJ, 24/Oct/2009
		void inv(Field<symmTensor>& tf, const UList<symmTensor>& tf1)
	{
		if (tf.empty())
		{
			return;
		}

		scalar scale = magSqr(tf1[0]);

		// Fixed terrible hack.  HJ, 20/Jan/2011
		boolList removeCmpts(3);
		removeCmpts[0] = magSqr(tf1[0].xx()) / scale < SMALL;
		removeCmpts[1] = magSqr(tf1[0].yy()) / scale < SMALL;
		removeCmpts[2] = magSqr(tf1[0].zz()) / scale < SMALL;

		if (removeCmpts[0] || removeCmpts[1] || removeCmpts[2])
		{
			symmTensorField tf1Plus(tf1);

			if (removeCmpts[0])
			{
				tf1Plus += symmTensor(1, 0, 0, 0, 0, 0);
			}

			if (removeCmpts[1])
			{
				tf1Plus += symmTensor(0, 0, 0, 1, 0, 0);
			}

			if (removeCmpts[2])
			{
				tf1Plus += symmTensor(0, 0, 0, 0, 0, 1);
			}

			TFOR_ALL_F_OP_FUNC_F(symmTensor, tf, =, inv, symmTensor, tf1Plus)

				if (removeCmpts[0])
				{
					tf -= symmTensor(1, 0, 0, 0, 0, 0);
				}

			if (removeCmpts[1])
			{
				tf -= symmTensor(0, 0, 0, 1, 0, 0);
			}

			if (removeCmpts[2])
			{
				tf -= symmTensor(0, 0, 0, 0, 0, 1);
			}
		}
		else
		{
			TFOR_ALL_F_OP_FUNC_F(symmTensor, tf, =, inv, symmTensor, tf1)
		}
	}

	tmp<symmTensorField> inv(const UList<symmTensor>& tf)
	{
		tmp<symmTensorField> result(new symmTensorField(tf.size()));
		inv(result(), tf);
		return result;
	}


	tmp<symmTensorField> inv(const tmp<symmTensorField>& tf)
	{
		tmp<symmTensorField> tRes = reuseTmp<symmTensor, symmTensor>::New(tf);
		inv(tRes(), tf());
		reuseTmp<symmTensor, symmTensor>::clear(tf);
		return tRes;
	}


	template<>
	tmp<Field<symmTensor> > transformFieldMask<symmTensor>
		(
			const tensorField& tf
			)
	{
		return symm(tf);
	}

	template<>
	tmp<Field<symmTensor> > transformFieldMask<symmTensor>
		(
			const tmp<tensorField>& ttf
			)
	{
		tmp<Field<symmTensor> > ret = transformFieldMask<symmTensor>(ttf());
		ttf.clear();
		return ret;
	}


	template<>
	tmp<Field<symmTensor> > transformFieldMask<symmTensor>
		(
			const symmTensorField& stf
			)
	{
		return stf;
	}

	template<>
	tmp<Field<symmTensor> > transformFieldMask<symmTensor>
		(
			const tmp<symmTensorField>& tstf
			)
	{
		return tstf;
	}


	// * * * * * * * * * * * * * * * global operators  * * * * * * * * * * * * * //

	void hdual(Field<vector>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_OP_F(vector, res, =, *, symmTensor, f)
	} 
	tmp<Field<vector>> operator *(const UList<symmTensor>& f)
	{
		tmp<Field<vector>> tRes(new Field<vector>(f.size())); hdual(tRes(), f); return tRes;
	} 
	tmp<Field<vector>> operator *(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, symmTensor>::New(tf); hdual(tRes(), tf()); reuseTmp<vector, symmTensor>::clear(tf); return tRes;
	}

		
	void dot ( Field<tensor>& res, const UList<symmTensor>& f1, const UList<symmTensor>& f2 )
	{
		TFOR_ALL_F_OP_F_OP_F(tensor, res, =, symmTensor, f1, &, symmTensor, f2)
	} 
	tmp<Field<tensor>> operator & ( const UList<symmTensor>& f1, const UList<symmTensor>& f2 )
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f1.size())); dot(tRes(), f1, f2); return tRes;
	}
	tmp<Field<tensor>> operator & ( const UList<symmTensor>& f1, const tmp<Field<symmTensor>>& tf2 )
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, symmTensor>::New(tf2); dot(tRes(), f1, tf2()); reuseTmp<tensor, symmTensor>::clear(tf2); return tRes;
	} 
	tmp<Field<tensor>> operator & ( const tmp<Field<symmTensor>>& tf1, const UList<symmTensor>& f2 )
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, symmTensor>::New(tf1); dot(tRes(), tf1(), f2); reuseTmp<tensor, symmTensor>::clear(tf1); return tRes;
	} 
	tmp<Field<tensor>> operator & ( const tmp<Field<symmTensor>>& tf1, const tmp<Field<symmTensor>>& tf2 )
	{
		tmp<Field<tensor>> tRes = reuseTmpTmp<tensor, symmTensor, symmTensor, symmTensor>::New(tf1, tf2); dot(tRes(), tf1(), tf2()); reuseTmpTmp<tensor, symmTensor, symmTensor, symmTensor>::clear(tf1, tf2); return tRes;
	}
		
	void dot ( Field<tensor>& res, const symmTensor& s1, const UList<symmTensor>& f2 )
	{
		TFOR_ALL_F_OP_S_OP_F(tensor, res, =, symmTensor, s1, &, symmTensor, f2)
	} 
	tmp<Field<tensor>> operator & ( const symmTensor& s1, const UList<symmTensor>& f2 )
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f2.size())); dot(tRes(), s1, f2); return tRes;
	} 
	tmp<Field<tensor>> operator & ( const symmTensor& s1, const tmp<Field<symmTensor>>& tf2 )
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, symmTensor>::New(tf2); dot(tRes(), s1, tf2()); reuseTmp<tensor, symmTensor>::clear(tf2); return tRes;
	} 
	void dot ( Field<tensor>& res, const UList<symmTensor>& f1, const symmTensor& s2 )
	{
		TFOR_ALL_F_OP_F_OP_S(tensor, res, =, symmTensor, f1, &, symmTensor, s2)
	}
	tmp<Field<tensor>> operator & ( const UList<symmTensor>& f1, const symmTensor& s2 )
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f1.size())); dot(tRes(), f1, s2); return tRes;
	} 
	tmp<Field<tensor>> operator & ( const tmp<Field<symmTensor>>& tf1, const symmTensor& s2 )
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, symmTensor>::New(tf1); dot(tRes(), tf1(), s2); reuseTmp<tensor, symmTensor>::clear(tf1); return tRes;
	}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>