#include <tensorField.hxx>

#include <transformField.hxx>
#include <boolList.hxx>

#define TEMPLATE
#include <FieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

	void tr(Field<scalar>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::tr, tensor, f)
	} 
	tmp<Field<scalar>> tr(const UList<tensor>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size())); tr(tRes(), f); return tRes;
	} 
	tmp<Field<scalar>> tr(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, tensor>::New(tf); tr(tRes(), tf()); reuseTmp<scalar, tensor>::clear(tf); return tRes;
	}
		
	void sph(Field<sphericalTensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor, res, =, ::tnbLib::sph, tensor, f)
	} 
	tmp<Field<sphericalTensor>> sph(const UList<tensor>& f)
	{
		tmp<Field<sphericalTensor>> tRes(new Field<sphericalTensor>(f.size())); sph(tRes(), f); return tRes;
	} 
	tmp<Field<sphericalTensor>> sph(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<sphericalTensor>> tRes = reuseTmp<sphericalTensor, tensor>::New(tf); sph(tRes(), tf()); reuseTmp<sphericalTensor, tensor>::clear(tf); return tRes;
	}
		
	void symm(Field<symmTensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::symm, tensor, f)
	} 
	tmp<Field<symmTensor>> symm(const UList<tensor>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size())); symm(tRes(), f); return tRes;
	} 
	tmp<Field<symmTensor>> symm(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, tensor>::New(tf); symm(tRes(), tf()); reuseTmp<symmTensor, tensor>::clear(tf); return tRes;
	}
		
	void twoSymm(Field<symmTensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(symmTensor, res, =, ::tnbLib::twoSymm, tensor, f)
	} 
	tmp<Field<symmTensor>> twoSymm(const UList<tensor>& f)
	{
		tmp<Field<symmTensor>> tRes(new Field<symmTensor>(f.size())); twoSymm(tRes(), f); return tRes;
	} 
	tmp<Field<symmTensor>> twoSymm(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<symmTensor>> tRes = reuseTmp<symmTensor, tensor>::New(tf); twoSymm(tRes(), tf()); reuseTmp<symmTensor, tensor>::clear(tf); return tRes;
	}
		
	void skew(Field<tensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor, res, =, ::tnbLib::skew, tensor, f)
	} 
	tmp<Field<tensor>> skew(const UList<tensor>& f)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f.size())); skew(tRes(), f); return tRes;
	} 
	tmp<Field<tensor>> skew(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf); skew(tRes(), tf()); reuseTmp<tensor, tensor>::clear(tf); return tRes;
	}
		
	void dev(Field<tensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor, res, =, ::tnbLib::dev, tensor, f)
	} 
	tmp<Field<tensor>> dev(const UList<tensor>& f)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f.size())); dev(tRes(), f); return tRes;
	} 
	tmp<Field<tensor>> dev(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf); dev(tRes(), tf()); reuseTmp<tensor, tensor>::clear(tf); return tRes;
	}
		
	void dev2(Field<tensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor, res, =, ::tnbLib::dev2, tensor, f)
	} 
	tmp<Field<tensor>> dev2(const UList<tensor>& f)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f.size())); dev2(tRes(), f); return tRes;
	} 
	tmp<Field<tensor>> dev2(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf); dev2(tRes(), tf()); reuseTmp<tensor, tensor>::clear(tf); return tRes;
	}
		
	void det(Field<scalar>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::det, tensor, f)
	} 
	tmp<Field<scalar>> det(const UList<tensor>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size())); det(tRes(), f); return tRes;
	} 
	tmp<Field<scalar>> det(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, tensor>::New(tf); det(tRes(), tf()); reuseTmp<scalar, tensor>::clear(tf); return tRes;
	}
		
	void cof(Field<tensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor, res, =, ::tnbLib::cof, tensor, f)
	} 

	tmp<Field<tensor>> cof(const UList<tensor>& f)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f.size())); cof(tRes(), f); return tRes;
	} 

	tmp<Field<tensor>> cof(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf); cof(tRes(), tf()); reuseTmp<tensor, tensor>::clear(tf); return tRes;
	}

	void hinv(Field<tensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor, res, =, ::tnbLib::hinv, tensor, f)
	} 

	tmp<Field<tensor>> hinv(const UList<tensor>& f)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f.size())); hinv(tRes(), f); return tRes;
	} 

	tmp<Field<tensor>> hinv(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf); hinv(tRes(), tf()); reuseTmp<tensor, tensor>::clear(tf); return tRes;
	}


		// This is a nasty hack for flat geometries.  For serious SVD, please use hinv
		// (Singular value decomposition and Householder transfromations)
		// HJ, 24/Oct/2009
		void inv(Field<tensor>& tf, const UList<tensor>& tf1)
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
			tensorField tf1Plus(tf1);

			if (removeCmpts[0])
			{
				tf1Plus += tensor(1, 0, 0, 0, 0, 0, 0, 0, 0);
			}

			if (removeCmpts[1])
			{
				tf1Plus += tensor(0, 0, 0, 0, 1, 0, 0, 0, 0);
			}

			if (removeCmpts[2])
			{
				tf1Plus += tensor(0, 0, 0, 0, 0, 0, 0, 0, 1);
			}

			TFOR_ALL_F_OP_FUNC_F(tensor, tf, =, inv, tensor, tf1Plus)

				if (removeCmpts[0])
				{
					tf -= tensor(1, 0, 0, 0, 0, 0, 0, 0, 0);
				}

			if (removeCmpts[1])
			{
				tf -= tensor(0, 0, 0, 0, 1, 0, 0, 0, 0);
			}

			if (removeCmpts[2])
			{
				tf -= tensor(0, 0, 0, 0, 0, 0, 0, 0, 1);
			}
		}
		else
		{
			TFOR_ALL_F_OP_FUNC_F(tensor, tf, =, inv, tensor, tf1)
		}
	}


	tmp<tensorField> inv(const UList<tensor>& tf)
	{
		tmp<tensorField> result(new tensorField(tf.size()));
		inv(result(), tf);
		return result;
	}


	tmp<tensorField> inv(const tmp<tensorField>& tf)
	{
		tmp<tensorField> tRes = reuseTmp<tensor, tensor>::New(tf);
		inv(tRes(), tf());
		reuseTmp<tensor, tensor>::clear(tf);
		return tRes;
	}


	void eigenValues(Field<vector>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(vector, res, =, ::tnbLib::eigenValues, tensor, f)
	} 
	tmp<Field<vector>> eigenValues(const UList<tensor>& f)
	{
		tmp<Field<vector>> tRes(new Field<vector>(f.size())); eigenValues(tRes(), f); return tRes;
	} 
	tmp<Field<vector>> eigenValues(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, tensor>::New(tf); eigenValues(tRes(), tf()); reuseTmp<vector, tensor>::clear(tf); return tRes;
	}
		
	void eigenVectors(Field<tensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor, res, =, ::tnbLib::eigenVectors, tensor, f)
	} 
	tmp<Field<tensor>> eigenVectors(const UList<tensor>& f)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f.size())); eigenVectors(tRes(), f); return tRes;
	} 
	tmp<Field<tensor>> eigenVectors(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf); eigenVectors(tRes(), tf()); reuseTmp<tensor, tensor>::clear(tf); return tRes;
	}

		
	void eigenValues(Field<vector>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(vector, res, =, ::tnbLib::eigenValues, symmTensor, f)
	} 
	tmp<Field<vector>> eigenValues(const UList<symmTensor>& f)
	{
		tmp<Field<vector>> tRes(new Field<vector>(f.size())); eigenValues(tRes(), f); return tRes;
	} 
	tmp<Field<vector>> eigenValues(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, symmTensor>::New(tf); eigenValues(tRes(), tf()); reuseTmp<vector, symmTensor>::clear(tf); return tRes;
	}
		
	void eigenVectors(Field<tensor>& res, const UList<symmTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(tensor, res, =, ::tnbLib::eigenVectors, symmTensor, f)
	} 
	tmp<Field<tensor>> eigenVectors(const UList<symmTensor>& f)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f.size())); eigenVectors(tRes(), f); return tRes;
	} 
	tmp<Field<tensor>> eigenVectors(const tmp<Field<symmTensor>>& tf)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, symmTensor>::New(tf); eigenVectors(tRes(), tf()); reuseTmp<tensor, symmTensor>::clear(tf); return tRes;
	}


		template<>
	tmp<Field<tensor> > transformFieldMask<tensor>
		(
			const symmTensorField& stf
			)
	{
		tmp<tensorField> tRes(new tensorField(stf.size()));
		tensorField& res = tRes();
		TFOR_ALL_F_OP_F(tensor, res, =, symmTensor, stf)
			return tRes;
	}

	template<>
	tmp<Field<tensor> > transformFieldMask<tensor>
		(
			const tmp<symmTensorField>& tstf
			)
	{
		tmp<Field<tensor> > ret = transformFieldMask<tensor>(tstf());
		tstf.clear();
		return ret;
	}


	void scaleRow ( Field<tensor>& res, const UList<tensor>& f1, const UList<vector>& f2 )
	{
		TFOR_ALL_F_OP_FUNC_F_F ( tensor, res, =, ::tnbLib::scaleRow, tensor, f1, vector, f2 )
	} 
	tmp<Field<tensor>> scaleRow ( const UList<tensor>& f1, const UList<vector>& f2 )
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f1.size())); scaleRow(tRes(), f1, f2); return tRes;
	} 
	tmp<Field<tensor>> scaleRow ( const UList<tensor>& f1, const tmp<Field<vector>>& tf2 )
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, vector>::New(tf2); scaleRow(tRes(), f1, tf2()); reuseTmp<tensor, vector>::clear(tf2); return tRes;
	} 
	tmp<Field<tensor>> scaleRow ( const tmp<Field<tensor>>& tf1, const UList<vector>& f2 )
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf1); scaleRow(tRes(), tf1(), f2); reuseTmp<tensor, tensor>::clear(tf1); return tRes;
	} 
	tmp<Field<tensor>> scaleRow ( const tmp<Field<tensor>>& tf1, const tmp<Field<vector>>& tf2 )
	{
		tmp<Field<tensor>> tRes = reuseTmpTmp<tensor, tensor, tensor, vector>::New(tf1, tf2); scaleRow(tRes(), tf1(), tf2()); reuseTmpTmp<tensor, tensor, tensor, vector>::clear(tf1, tf2); return tRes;
	}
		
	void scaleRow ( Field<tensor>& res, const tensor& s1, const UList<vector>& f2 )
	{
		TFOR_ALL_F_OP_FUNC_S_F ( tensor, res, =, ::tnbLib::scaleRow, tensor, s1, vector, f2 )
	} 
	tmp<Field<tensor>> scaleRow ( const tensor& s1, const UList<vector>& f2 )
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f2.size())); scaleRow(tRes(), s1, f2); return tRes;
	} 
	tmp<Field<tensor>> scaleRow ( const tensor& s1, const tmp<Field<vector>>& tf2 )
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, vector>::New(tf2); scaleRow(tRes(), s1, tf2()); reuseTmp<tensor, vector>::clear(tf2); return tRes;
	} 
	void scaleRow ( Field<tensor>& res, const UList<tensor>& f1, const vector& s2 )
	{
		TFOR_ALL_F_OP_FUNC_F_S ( tensor, res, =, ::tnbLib::scaleRow, tensor, f1, vector, s2 )
	} 
	tmp<Field<tensor>> scaleRow ( const UList<tensor>& f1, const vector& s2 )
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f1.size())); scaleRow(tRes(), f1, s2); return tRes;
	} 
	tmp<Field<tensor>> scaleRow ( const tmp<Field<tensor>>& tf1, const vector& s2 )
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf1); scaleRow(tRes(), tf1(), s2); reuseTmp<tensor, tensor>::clear(tf1); return tRes;
	}


		// * * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * //

		
	void hdual(Field<vector>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_OP_F(vector, res, =, *, tensor, f)
	} 
	tmp<Field<vector>> operator *(const UList<tensor>& f)
	{
		tmp<Field<vector>> tRes(new Field<vector>(f.size())); hdual(tRes(), f); return tRes;
	} 
	tmp<Field<vector>> operator *(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, tensor>::New(tf); hdual(tRes(), tf()); reuseTmp<vector, tensor>::clear(tf); return tRes;
	}
		
	void hdual(Field<tensor>& res, const UList<vector>& f)
	{
		TFOR_ALL_F_OP_OP_F(tensor, res, =, *, vector, f)
	} 
	tmp<Field<tensor>> operator *(const UList<vector>& f)
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f.size())); hdual(tRes(), f); return tRes;
	} 
	tmp<Field<tensor>> operator *(const tmp<Field<vector>>& tf)
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, vector>::New(tf); hdual(tRes(), tf()); reuseTmp<tensor, vector>::clear(tf); return tRes;
	}

		
	void divide ( Field<vector>& res, const UList<vector>& f1, const UList<tensor>& f2 )
	{
		TFOR_ALL_F_OP_F_OP_F(vector, res, =, vector, f1, /, tensor, f2)
	} 
	tmp<Field<vector>> operator / ( const UList<vector>& f1, const UList<tensor>& f2 )
	{
		tmp<Field<vector>> tRes(new Field<vector>(f1.size())); divide(tRes(), f1, f2); return tRes;
	} 
	tmp<Field<vector>> operator / ( const UList<vector>& f1, const tmp<Field<tensor>>& tf2 )
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, tensor>::New(tf2); divide(tRes(), f1, tf2()); reuseTmp<vector, tensor>::clear(tf2); return tRes;
	} 
	tmp<Field<vector>> operator / ( const tmp<Field<vector>>& tf1, const UList<tensor>& f2 )
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, vector>::New(tf1); divide(tRes(), tf1(), f2); reuseTmp<vector, vector>::clear(tf1); return tRes;
	} 
	tmp<Field<vector>> operator / ( const tmp<Field<vector>>& tf1, const tmp<Field<tensor>>& tf2 )
	{
		tmp<Field<vector>> tRes = reuseTmpTmp<vector, vector, vector, tensor>::New(tf1, tf2); divide(tRes(), tf1(), tf2()); reuseTmpTmp<vector, vector, vector, tensor>::clear(tf1, tf2); return tRes;
	}
		
	void divide ( Field<vector>& res, const vector& s1, const UList<tensor>& f2 )
	{
		TFOR_ALL_F_OP_S_OP_F(vector, res, =, vector, s1, /, tensor, f2)
	} 
	tmp<Field<vector>> operator / ( const vector& s1, const UList<tensor>& f2 )
	{
		tmp<Field<vector>> tRes(new Field<vector>(f2.size())); divide(tRes(), s1, f2); return tRes;
	} 
	
	tmp<Field<vector>> operator / ( const vector& s1, const tmp<Field<tensor>>& tf2 )
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, tensor>::New(tf2); divide(tRes(), s1, tf2()); reuseTmp<vector, tensor>::clear(tf2); return tRes;
	}
	void divide ( Field<vector>& res, const UList<vector>& f1, const tensor& s2 )
	{
		TFOR_ALL_F_OP_F_OP_S(vector, res, =, vector, f1, /, tensor, s2)
	} 
	tmp<Field<vector>> operator / ( const UList<vector>& f1, const tensor& s2 )
	{
		tmp<Field<vector>> tRes(new Field<vector>(f1.size())); divide(tRes(), f1, s2); return tRes;
	} 
	tmp<Field<vector>> operator / ( const tmp<Field<vector>>& tf1, const tensor& s2 )
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, vector>::New(tf1); divide(tRes(), tf1(), s2); reuseTmp<vector, vector>::clear(tf1); return tRes;
	}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>