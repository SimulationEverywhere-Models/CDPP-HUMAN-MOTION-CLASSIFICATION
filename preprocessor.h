/*******************************************************************
*
*  DESCRIPTION: Atomic Model preprocessor
*
*  AUTHOR: Seyed Ali Etemad
*
*  EMAIL: mailto://etemad@sce.carleton.ca
*
*  DATE: 4/11/2009
*
*******************************************************************/

#ifndef __PREPROCESSOR_H
#define __PREPROCESSOR_H

//#include <list>
#include "atomic.h"     // class Atomic

class Preprocessor : public Atomic
{
public:
	Preprocessor( const string &name = "Preprocessor" );		//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &DIn;
	Port &DP;
	Time preparationTime;


};	// class Preprocessor

// ** inline ** //
inline
string Preprocessor::className() const
{
	return "Preprocessor" ;
}

#endif   //__PREPROCESSOR_H
