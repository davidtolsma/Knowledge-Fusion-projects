---------------------------------------------------------------------------------
	Sets Layer visibility

	Input : (Integer) 	Layer (1-255)

	Input : (String) 	Visibility (work, selectable, visible, invisible)

				Error is generated if the input is not valid.

	Return: (Boolean)	- TRUE if the layer is set, 
                           	  otherwise, FALSE.

	Example: (Boolean) SetLayer: SetLayer( 2, "work");
---------------------------------------------------------------------------------

---------------------------------------------------------------------------------
	Sets a Range of Layers visibility

	Input : (List) 		{$low(Integer), $high(Integer)}

	Input : (String) 	Visibility (work, selectable, visible, invisible)

				Error is generated if the input is not valid.

	Return: (Boolean)	- TRUE if the layer is set, 
				  otherwise, FALSE.

	Example: (Boolean) SetLayerRange: SetLayer_Range( {10 ,20}, "visible");
---------------------------------------------------------------------------------

---------------------------------------------------------------------------------
	Get a Layers visibility

	Input : (Integer) 	Layer (1-255)

				Error is generated if the input is not valid.

	Return: (String)	- The layers visibility, 
				  (work, selectable, visible, invisible)

	Example: (String) GetLayer: GetLayerInfo( 2 );
---------------------------------------------------------------------------------

---------------------------------------------------------------------------------
	Gets a Range of Layers visibility

	Input : (List) 		{$low(Integer), $high(Integer)}

				Error is generated if the input is not valid.

	Return: (List)		- List of Lists {layer(Integer), visibility(String)}
				  visibility (work, selectable, visible, invisible)

	Example: (List) GetLayer_Range: GetLayer_Range( {10, 20} );
---------------------------------------------------------------------------------

---------------------------------------------------------------------------------
	Gets all Layers visibility

	Return: (List)		- List of Lists {layer(Integer), visibility(String)}
				  visibility (work, selectable, visible, invisible)

	Example: (List) GetLayer_All: GetLayer_All();
---------------------------------------------------------------------------------

