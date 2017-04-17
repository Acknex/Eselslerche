//////////////////////////////////////////////////
//////////Postprocessing Helperfunctions//////////
//////////////////////////////////////////////////
////08.03.2008////////////////by Nils Daumann/////
/////////////slindev.wordpress.com////////////////
//////////////////////////////////////////////////


//temporary pointers
VIEW* PP_Temp_View;


//Add an effect to a views stage chain
VIEW* PP_Add(VIEW* View, MATERIAL* Material,BMAP* bmap)
{
	//find the last view of "View"s effectchain and store its pointer
	PP_Temp_View = View;
	while(PP_Temp_View.stage != NULL)
	{
		PP_Temp_View = PP_Temp_View.stage;
	}
	
	//create a new view as the stored views stage
	PP_Temp_View.stage = view_create(0);
	set(PP_Temp_View.stage,PROCESS_TARGET);
	
	//assign "Material" to the just created view
	PP_Temp_View = PP_Temp_View.stage;
	PP_Temp_View.material = Material;
	
	//if a bmap is given, render the view into it
	if(bmap != NULL)
	{
		PP_Temp_View.bmap = bmap;
	}
	
	//return the pointer to the new view
	return(PP_Temp_View);
}


//remove an effect from a views stage chain
int PP_Remove(VIEW* View, MATERIAL* Material,VIEW* StageView)
{
	//find the view with the material selected or "StageView" and the previous view
	PP_Temp_View = View;
	while(PP_Temp_View.material != Material && ((StageView == NULL)+(PP_Temp_View.stage != NULL)) != 0)
	{
		View = PP_Temp_View;
		PP_Temp_View = PP_Temp_View.stage;
		
		//return one if the stage doesn´t exist
		if(PP_Temp_View == NULL){return(1);}
	}
	
	//pass the views stage to the previous view
	View.stage = PP_Temp_View.stage;
	
	//pass the render target
	View.bmap = PP_Temp_View.bmap;
	
	//reset the views bmap to null
	PP_Temp_View.bmap = NULL;
	
	//remove the view
	ptr_remove(PP_Temp_View);
	
	//return null if everything worked
	return(0);
}


//remove all postprocessing from the view
void PP_Remove_All(VIEW* View)
{
	if(View.stage == NULL){return;}
	PP_Temp_View = View.stage;
	View.stage = NULL;
	View.bmap = NULL;
	while(PP_Temp_View.stage != NULL)
	{
		View = PP_Temp_View;
		PP_Temp_View = View.stage;
		
		//pass the views stage to the previous view
		View.stage = NULL;
		
		//reset the views bmap to null
		View.bmap = NULL;
		
		//remove the view
		ptr_remove(View);
	}
}


//returns the pointer to the viewchains last view
VIEW* PP_LastView(VIEW* View)
{
	//find the last view of "View"s effectchain and store its pointer
	PP_Temp_View = View;
	while(PP_Temp_View.stage != NULL)
	{
		PP_Temp_View = PP_Temp_View.stage;
	}
	
	//return the pointer
	return(PP_Temp_View);
}