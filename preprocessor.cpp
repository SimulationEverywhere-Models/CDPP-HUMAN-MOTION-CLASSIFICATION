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

/** include files **/
#include "preprocessor.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Preprocessor
********************************************************************/
Preprocessor::Preprocessor( const string &name )
: Atomic( name )
, DIn( addInputPort( "DIn" ) )
, DP( addOutputPort( "DP" ) )
, preparationTime( 0, 0, 5, 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
	preparationTime = time ;
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &Preprocessor::initFunction()
{
	this-> passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
********************************************************************/
Model &Preprocessor::externalFunction( const ExternalMessage &msg )
{
	if (this->state() == passive)
	{
		holdIn( active, preparationTime );
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Preprocessor::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Preprocessor::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), DP, 1) ;
	return *this ;
}
