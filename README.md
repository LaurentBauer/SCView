# SCView
 
SCView is a Step Express data viewer<br/>
SCView stands for [StepCode](http://stepcode.org/mw/index.php?title=STEPcode) View <br/>

[![](https://github.com/LaurentBauer/SCView/wiki/img/SCLView.png)](https://youtu.be/ig9xq1H828M)

## Features

### One model
* SCView stores one data model : the express schema
* Multi models support may come (?)

### 3 views 
SCView delivers 3 views of the same model
* The tree view
* The Express-G view : a diagram based representation
* The Express text view

### Search / find
* At the top right corner of the window, the find function (Ctrl+F) provides search with completion<br/>
<img src="https://github.com/LaurentBauer/SCView/wiki/img/search_002.png">

### Tree View
<img src="https://github.com/LaurentBauer/SCView/wiki/img/Tree_001.png">
* The top Item represents the schema. It has two children:
* The list of entities
* The list of types
* Lists display their children

**Navigation** <br/>
Selecting one entity or type in the tree will display the selection in the two other views

**Show / Hide** with F3

### The Express-G view
<img src="https://github.com/LaurentBauer/SCView/wiki/img/EG_010.png">
* Delivers a diagram representation of the currently selected Entity <br/>
* The composition structure is partially implemented
* The inheritance view is NOT implemented
* other features like cardinality, rules... are NOT implemented

**Navigation** <br/>
Double clicking one entity or type will display the selection in the two other views

### The Express Text Editor
<img src="https://github.com/LaurentBauer/SCView/wiki/img/textView.png">
* Displays the selected entity/type in the Express format 
* Has a syntax highlighter 
* Is Read only : no edition features !
* Has mouse tracking over objects and popup as tooltip the express description
* Provides Hypertext-like navigation

**The Highlighter** 
* Types
* Entities
* Simple Types
* Some keywords

**Navigation** <br/>
Double clicking one entity or type will display the selection in the two other views

**Show / Hide** with F4

### Standard undo / redo
* Undo with Ctrl+Z 
* Redo with Ctrl+Y
* To navigate backward / forward 

### Express-G supported features


<TABLE BORDER="0">
  <CAPTION> Types and diagram representation </CAPTION>
  <TR>
   <TH> Type Description </TH>
   <TH> Express Definition </TH>
   <TH> Express-G Representation </TH>
  </TR>

 <TR>
  <TD> Basic types </TD>
  <TD> Keywords <br />
   <ul>
    <li> INTEGER </li>
    <li> REAL </li>
    <li> BOOLEAN </li>
    <li> LOGICAL </li>
    <li> STRING </li>
    <li> BINARY </li>
    <li> NUMBER </li>
   </ul>
 </TD>
  <TD>
   <IMG SRC="https://github.com/LaurentBauer/SCView/wiki/img/realTypeDiagram.png"
   ALT="Img: Basic type example">
  </TD>
 </TR>

 <TR>
  <TD> User Defined </TD>
  <TD> TYPE label = STRING; <br />
    END_TYPE; <br /> </TD>
  <TD>
   <IMG SRC="https://github.com/LaurentBauer/SCView/wiki/img/definedTypeDiagram.png"
   ALT="Img: Defined type">
  </TD>
 </TR>

 <TR>
  <TD> SELECT </TD>
  <TD> TYPE curve_on_surface = select <br/>
  (pcurve, <br/>
   surface_curve, <br/>
   composite_curve_on_surface); <br/>
END_TYPE; <br/> 
  </TD>
  <TD>
   <IMG SRC="https://github.com/LaurentBauer/SCView/wiki/img/selectTypeDiagram.png"
   ALT="Img: Select type">
  </TD>
 </TR>

 <TR>
  <TD> ENUMERATION </TD>
  <TD> TYPE marker_type = ENUMERATION OF <br/>
  (dot, x, plus, asterisk, ring, square, triangle);<br/>
   END_TYPE;
  </TD>
  <TD>
   <IMG SRC="https://github.com/LaurentBauer/SCView/wiki/img/enumTypeDiagram.png"
   ALT="Img: Enum type">
  </TD>
 </TR>

</TABLE> 



### And that's all for now...


## Dependencies
Based on [STEP-Code](https://github.com/stepcode/stepcode) and [Qt](http://qt-project.org/)

## Warning:
* Development version
* Partial implementation of Express, especially Express-G
* Use it for test, DO NOT use it in production / operation
* Made for fun
