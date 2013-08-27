/* List of object IDs */
 call RxFuncAdd 'SysLoadFuncs', 'rexxutil', 'SysLoadFuncs'
 call SysLoadFuncs
 App='PM_Workplace:Location'
 
 call SysINI 'USER', App, 'All:', 'Keys'
 if result \= 'Error:' then do
   call SysCls
   Say 'Listing of object ID information';Say '';
   parse value SysTextScreenSize() with row col
   j=row-5
   do i=1 to Keys.0
     if trunc(i/j)==i/j then
     do
       Say '';Say 'Press any key to display the next screen...'
       key=SysGetKey()
       call SysCls
       Say 'Listing of object ID information';Say '';
     end
     Say Keys.i
   end
 end
 else Say 'Error querying for' App
 return
