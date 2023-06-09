/*******************************************************************
*
*  DESCRIPTION: Atomic Model classifier
*
*  AUTHOR: Seyed Ali Etemad
*
*  EMAIL: mailto://etemad@sce.carleton.ca
*
*  DATE: 4/11/2009
*
*******************************************************************/

#ifndef __CLASSIFIER_H
#define __CLASSIFIER_H

//#include <list>
#include "atomic.h"     // class Atomic

class Classifier : public Atomic
{
public:
	Classifier( const string &name = "Classifier" );			//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &result, &trainAcc;
	Port &DP;
	Time preparationTime;
	int counter;
	int testprob;

	enum State{
		Training,
		Send_Training_Result,
		Testing,
		Send_Testing_Result,
		};
	State state;

};	// class Classifier

// ** inline ** //
inline
string Classifier::className() const
{
	return "Classifier" ;
}

#endif   //__CLASSIFIER_H
