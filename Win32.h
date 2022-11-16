
/*

	Headers and Linkers:-

	#include <comctrl32.h> -lcomctl32
	#include <uxtheme.h> -luxtheme



*/



/*

Macros for All Widget Creation

*/

#ifdef _WIN32

#include <windows.h>
#include <windowsx.h>
#include <winuser.h>
#include <commctrl.h>
#include <uxtheme.h>


 

#define dflt WS_CHILD | WS_VISIBLE

#define Progressbar(parent,style,posX,posY,sizeX,sizeY)\
CreateWindow( PROGRESS_CLASS, NULL,style | WS_VISIBLE | WS_CHILD ,posX, posY, sizeX, sizeY,parent, NULL,NULL , NULL);

#define Label(parent,content,style,posX,posY,sizeX,sizeY)\
CreateWindow("STATIC", content, style | WS_VISIBLE | WS_CHILD, posX, posY, sizeX, sizeY, parent, (HMENU)NULL, (HINSTANCE)GetWindowLong(parent, GWL_HINSTANCE), NULL);


#define Button(parent, content, style, posX, posY, sizeX, sizeY, ID)\
CreateWindow("BUTTON", content,  style | WS_VISIBLE | WS_CHILD  ,  posX, posY,   sizeX,    sizeY, parent,    (HMENU)ID, (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE), NULL);      // Pointer not needed.			 


#define GroupBox(parent,content,style,posX,posY,sizeX,sizeY)\
CreateWindow("BUTTON", content,  style | BS_GROUPBOX |WS_VISIBLE | WS_CHILD,  posX, posY,   sizeX,    sizeY, parent,    (HMENU)NULL, (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE), NULL);      // Pointer not needed.			 


#define CheckBox(parent,content,style,posX,posY,sizeX,sizeY,ID)\
CreateWindow("BUTTON", content,  style | BS_AUTOCHECKBOX | WS_VISIBLE | WS_CHILD,  posX, posY,   sizeX,    sizeY, parent,    (HMENU)ID, (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE), NULL);      // Pointer not needed.			 

#define Radio(parent,content,style,posX,posY,sizeX,sizeY,ID)\
CreateWindow("BUTTON", content,  style | BS_AUTORADIOBUTTON | WS_VISIBLE | WS_CHILD,  posX, posY,   sizeX,    sizeY, parent,    (HMENU)ID, (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE), NULL);      // Pointer not needed.			 

#define Input(parent,style,posX,posY,sizeX,sizeY)\
Entry(parent,style,posX,posY,sizeX,sizeY)

#define Entry(parent,style,posX,posY,sizeX,sizeY)\
CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL | ES_WANTRETURN, posX, posY, sizeX, sizeY, parent, (HMENU)0, NULL, 0);

#define IP(parent,style,posX,posY,sizeX,sizeY)\
IPEntry(parent,style,posX,posY,sizeX,sizeY)

#define IPEntry(parent,style,posX,posY,sizeX,sizeY)\
CreateWindow(WC_IPADDRESS, "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL | ES_WANTRETURN, posX, posY, sizeX, sizeY, parent, (HMENU)0, NULL, 0);



#define Password(parent,style,posX,posY,sizeX,sizeY)\
CreateWindow("EDIT","",WS_VISIBLE|WS_BORDER|WS_CHILD|ES_PASSWORD,posX,posY,sizeX,sizeY,parent,NULL,GetModuleHandle(NULL),NULL);
			

#define Listbox(parent,style,posX,posY,sizeX,sizeY)\
CreateWindow( "LISTBOX",  NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | style, posX,   posY,  sizeX, sizeY, parent,NULL,hInst,NULL);

#define Listview(parent,style,posX,posY,sizeX,sizeY)\
CreateWindow(  WC_LISTVIEW, NULL, style | WS_VISIBLE | WS_CHILD | WS_BORDER   , posX, posY, sizeX, sizeY, parent, NULL, NULL, NULL);

#define Dropdown(parent,posX,posY,sizeX,sizeY)\
CreateWindow(WC_COMBOBOX,TEXT("DUMMY"),CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,posX, posY, sizeX, sizeY, parent, NULL, NULL,NULL);

#define Range(parent,style,posX,posY,sizeX,sizeY,ID)\
CreateWindow(  TRACKBAR_CLASS, "Trackbar Control", WS_CHILD | WS_VISIBLE | style |TBS_ENABLESELRANGE,posX, posY,sizeX, sizeY,hwnd,(HMENU)ID,NULL, NULL ); 


#define STATIC_BG_ALL_DEFWBG return (INT_PTR)(HBRUSH)(COLOR_WINDOW+1);  // Default Window Background Color to all static windows


     
/*This Will set font style to its normal form instead of using predefined bold style of win32
works with Buttons
		   Static Texts
		   Entry Box
		   etc
*/

void setDefaultTextStyle(HWND widget){
	SendMessage(widget, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
}

void PB_setColor(HWND progress,LPARAM COLOR){
	SendMessage( progress, PBM_SETBARCOLOR, 0 , COLOR);
	SendMessage(progress,(UINT) PBM_SETBARCOLOR,0,(LPARAM)COLOR);
}


void PB_setBGM(HWND progress,LPARAM COLOR){
	SendMessage( progress, PBM_SETBKCOLOR, 0 , COLOR);
	SendMessage(progress,(UINT) PBM_SETBARCOLOR,0,(LPARAM)COLOR);
}


void PB_setValue(HWND progress,WPARAM value){
	SendMessage(progress, PBM_SETPOS, value, 0);
}

void PB_setRange(HWND progress,LPARAM min ,LPARAM max){
	SendMessage(progress, PBM_SETRANGE, 0, MAKELPARAM(min, max));
}


void resetProgressRange(HWND progress){
	SendMessage(progress, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
}




/*

Functions Below are for modifying texts of a widget and for changing the font style

*/


void setText(HWND handle,char *content){
	SendMessage(handle,WM_SETTEXT,0,(LPARAM)content);
}


void setText(HWND handle,int len,char *content){
	SendMessage(handle,WM_GETTEXT,len,(LPARAM)content);
}

    


void setFont(HWND widget,int size,const char* font){
	HFONT hFont ;
	hFont=CreateFont (size, 0, 0, FW_NORMAL, FW_SEMIBOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, (LPCSTR)font);
    SendMessage (widget, WM_SETFONT, WPARAM (hFont), TRUE);
}





/*
		ONLY FOR STATIC TEXT CONTROLS
		
		the setFG sets foreground color of an element and setBG does set the background

*/


LRESULT setFG(WPARAM wParam,int R, int G ,int B){
	HDC hdcStatic = (HDC) wParam;
	SetTextColor(hdcStatic, RGB(R,G,B));
	return (LRESULT)GetStockObject(NULL_BRUSH);
}


LRESULT setBG(WPARAM wParam,int R, int G ,int B){
	HDC hdcStatic = (HDC) wParam;
	SetBkColor(hdcStatic, RGB(R,G,B));
	return (LRESULT)GetStockObject(NULL_BRUSH);
}


LRESULT setBGTransparent(WPARAM wParam){
	HDC hdcStatic = (HDC) wParam;
	SetBkMode(hdcStatic, TRANSPARENT);
	return (LRESULT)HBRUSH(GetStockObject(NULL_BRUSH));
}




/*

		Functions for ListBox control

*/



void LB_add(HWND hList,char content[]){
	SendMessage(hList, LB_ADDSTRING, 0, 
                    (LPARAM) content);
}



int LB_getSelIndex(HWND LB){
	    int count = SendMessage(LB, LB_GETCOUNT, 0, 0);
        int iSelected = -1;
        int i=0;
         // go through the items and find the first selected one
        for (i = 0; i < count; i++)
            {
            // check if this item is selected or not..
            if (SendMessage(LB, LB_GETSEL, i, 0) > 0)
                {
                            // yes, we only want the first selected so break.
                iSelected = i;
                break;
                }

            }
            
    return iSelected;
}

void LB_getText(HWND LB , int index , char* buffer){
	SendMessage(LB,LB_GETTEXT,index,(LPARAM)buffer);
}



int LB_itemCount(HWND LB){
	return SendMessage(LB,LB_GETCOUNT,0,0);
}



/*

Functions for ListView Controls

*/

int LV_getSelIndex(HWND LV){
			int iPos = ListView_GetNextItem(LV, -1, LVNI_SELECTED);
			while (iPos != -1) {
   			 // iPos is the index of a selected item
    		// do whatever you want with it
			return iPos;
    		// Get the next selected item
    		iPos = ListView_GetNextItem(LV, iPos, LVNI_SELECTED);
			}
}

void LV_removeItem(HWND LV , int itemIndex){
	ListView_DeleteItem(LV, itemIndex);
}


void LV_removeCol(HWND LV , int columnIndex){
	ListView_DeleteColumn(LV,columnIndex);
}


HWND LV_setColumns(HWND hListBox,char items[][255],int num,int width){
	LVCOLUMN lvc; 
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	
	
	if(width==0 || width == 0 || width<0){
		width=50;
	}
	
	int counter=0;
	

	
	for(counter=0;counter<num;counter++){
	
	
	lvc.iSubItem = counter;
	lvc.pszText = (LPSTR)items[counter];
	lvc.cx = width;
	lvc.fmt = LVCFMT_LEFT;
	ListView_InsertColumn(hListBox, counter, &lvc);
	
	}


	
}


void LV_clear(HWND LV){
	SendMessage(LV,LVM_DELETEALLITEMS,0,0);
}


int LV_itemCount(HWND LV){
	return SendMessage(LV,LVM_GETITEMCOUNT,0,0);
}




/*

	Functions for Trackbar controls, also known as range Slider

*/


void TB_setRange(HWND TB,int min , int max){
	SendMessage(TB,TBM_SETRANGE,1,MAKELPARAM(min,max));
}

int TB_getThumbPos(HWND TB){
	return SendMessage(TB,TBM_GETPOS,0,0);
}

void TB_setThumbPos(HWND TB,int value){
	SendMessage(TB,TBM_SETPOS,1,(LPARAM)value);
}




/*

	Functions for Combobox, usually known as Dropdown

*/

void CB_add(HWND hwnd,char str[]){
	SendMessage(hwnd,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) str);
}

int CB_getIndex(HWND CB){
	return SendMessage(CB,CB_GETCURSEL,0,0);
}

void CB_delete(HWND CB , int itemIndex){
	SendMessage(CB,CB_DELETESTRING,itemIndex,0);
}


void CB_getText(HWND CB , int index , char* buffer){
	SendMessage(CB,CB_GETLBTEXT,index,(LPARAM)buffer);
}

int CB_find(HWND CB,int startIndex,char string[]){
	return SendMessage(CB,CB_FINDSTRING,startIndex,(LPARAM)string);
}


int CB_itemCount(HWND CB){
	return SendMessage(CB,CB_GETCOUNT ,0,0);
}


// ----------------------------------------------------------------------------------------------------------------------------------------------------



int checked(HWND Button){ // To check the status of RADIOBUTTON or CHECKBOX
	return (Button_GetState(Button) == BST_CHECKED);
}


void getEntry(HWND edit , TCHAR* dest , int buffer){ // To take entries from a EDIT control,formerly known as TEXTBOX 
	GetWindowText(edit, dest, buffer);
}




#elif __linux__

printf("This file has specially been developped for programming Windows API only\n Thus it will not on any other platform");



#else

#endif
