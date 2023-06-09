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

/** include files **/
#include "Classifier.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include <stdio.h>
#include <stdlib.h>
#include "distri.h"        // class Distribution

/** public functions **/

/*******************************************************************
* Function Name: Classifier
********************************************************************/
Classifier::Classifier( const string &name )
: Atomic( name )
, DP( addInputPort( "DP" ) )
, trainAcc( addOutputPort( "trainAcc" ) )
, result( addOutputPort( "result" ) )
, preparationTime( 0, 0, 03, 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;
srand (2);
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &Classifier::initFunction()
{
	state = Training;
	counter = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
********************************************************************/
Model &Classifier::externalFunction( const ExternalMessage &msg )
{
	if( state == Training )
	{
		counter++;
		state = Send_Training_Result;
		holdIn( active, preparationTime );
	}
	else if (state == Testing)
	{
		state = Send_Testing_Result;
		holdIn( active, preparationTime );
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Classifier::internalFunction( const InternalMessage & )
{
	switch (state){
			case Send_Training_Result:
				if ((counter < 9) && (counter*10 < testprob))
					state = Training;
				else
					state = Testing;
				passivate();
				break;

			case Send_Testing_Result:
				state = Testing;
				passivate();
				break;
	};
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Classifier::outputFunction( const InternalMessage &msg )
{
	switch (state){
			case Send_Training_Result:
				testprob=rand()%100;
				if ((counter >= 9) || (counter*10 > testprob))
				sendOutput( msg.time(), trainAcc, 1) ;
				break;

			case Send_Testing_Result:
				sendOutput( msg.time(), result, (rand()% 5)+90 )  ;
				break;
	};
	return *this ;
}
