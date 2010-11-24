
#include <iostream>
#include <strstream>
#include <string>

#include <uf.h>
#include <uf_kf.h>
#include <uf_layer.h>
#include <ug_exception.hxx>
#include <ug_session.hxx>

#include "kf_layer.h"

namespace
{
    // Layer status constants
    const std::string workLayer = "work";
    const std::string selectableLayer = "selectable";
    const std::string visibleLayer = "visible";
    const std::string invisibleLayer = "invisible";

    int compareNoCase( const std::string& input, const std::string& s2 )
    {
        std::string::const_iterator p = input.begin(); //assigning status string
        std::string::const_iterator p2 = s2.begin(); //status constants

        while ( (p != input.end() ) && (p2 != s2.end() ) )
        {
            if ( toupper(*p) != toupper(*p2) ) //if the input and the constants don't match
                return ( ( toupper(*p) < toupper(*p2) ) ? -1 : 1 );
            ++p;
            ++p2;
        }
        return ( s2.size() - input.size() );
    }
}

void DPH_KF_set_layer( UF_KF_value_t *data, int num,
                              UF_KF_value_t *returnValue )
{
	try
	{
		UgSession session(true);

		int layer;
		char *statusStr;

		UgException::throwOnFailure(
            UF_KF_ask_integer( data[0], &layer ) ); //layer gets first argument (1-256)
		UgException::throwOnFailure(
            UF_KF_ask_string( data[1], &statusStr ) ); //statusStr gets second argument (work, visible, selectable, invisible)

        int layerStatus = UF_LAYER_INACTIVE_LAYER;

		// if statusStr (second argument) matches layer constants (e.g. workLayer), returns 0
		// then sets layerStatus to UF_LAYER_<type> (these are UGOPEN defined layer types)
        if ( compareNoCase( statusStr, workLayer ) == 0 )
        {
            layerStatus = UF_LAYER_WORK_LAYER;
        }
        else if ( compareNoCase( statusStr, selectableLayer ) == 0  )
        {
            layerStatus = UF_LAYER_ACTIVE_LAYER;
        }
        else if ( compareNoCase( statusStr, visibleLayer ) == 0  )
        {
            layerStatus = UF_LAYER_REFERENCE_LAYER;
        }
        else if ( compareNoCase( statusStr, invisibleLayer ) == 0  )
        {
            layerStatus = UF_LAYER_INACTIVE_LAYER;
        }
		else
		{
			// If the type doesn't mactch
			layerStatus = UF_LAYER_INACTIVE_LAYER;
		}

        //std::strstream msg;
        //msg << "Setting layer " << layer << " to status " << layerStatus << "\n" << std::ends;
        //UF_print_syslog( msg.str(), FALSE );
        UgException::throwOnFailure( UF_LAYER_set_status(layer, layerStatus ) ); //UF Call setting layer status else error

        UF_KF_make_integer( -1 );compareNoCase( statusStr, invisibleLayer ), returnValue );
        //UF_KF_make_boolean(true, returnValue ); //set the return value to True
    }
	catch (const UgException& err )
	{
		UF_print_syslog( const_cast<char*>(err.askErrorText().c_str()), FALSE );
        //UF_KF_make_integer(-1, returnValue );
		UF_KF_make_boolean(false, returnValue ); //set the return value to False
	}
}

void DPH_KF_get_layer( UF_KF_value_t *data, int num,
                              UF_KF_value_t *returnValue )
{
	try
	{
		UgSession session(true);
		UF_KF_type_t value_type;
		int layer;
		int status;

		UF_KF_ask_type( data[0], &value_type );
		if ( value_type != UF_KF_integer ) //Must be an integer passed in
		{
			UF_terminate();
			return;
		}

		UgException::throwOnFailure(
            UF_KF_ask_integer( data[0], &layer ) );

		UF_LAYER_ask_status(layer, &status);

		switch(status)
		{
			case UF_LAYER_WORK_LAYER:
                UF_KF_make_string(workLayer.c_str(), returnValue );
                break;
			case UF_LAYER_ACTIVE_LAYER:
                UF_KF_make_string(selectableLayer.c_str(), returnValue );
                break;
			case UF_LAYER_REFERENCE_LAYER:
                UF_KF_make_string(visibleLayer.c_str(), returnValue );
                break;
			case UF_LAYER_INACTIVE_LAYER:
                UF_KF_make_string(invisibleLayer.c_str(), returnValue );
                break;
			default:
                // need to flag an error using UF_KF_make_error
                //UF_KF_make_string ("NULL", &returnValue );
                break;
		}
	}
	catch (const UgException& err )
	{
		UF_print_syslog( const_cast<char*>(err.askErrorText().c_str()), FALSE );
	}
}

