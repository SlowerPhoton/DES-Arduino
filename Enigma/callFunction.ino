/**
   @file
   function callFunction() used to call the chosen function according to current lcdRow
*/

void callFunction() {

  switch (lcdRow) {
    case 0:
      generateKey();
      break;
    case 1:
      encrypt();
      break;
    case 2:
      resetShift();
      break;
    case 3:
      printShift();
      break;
    case 4:
      setShift();
      break;
    case 5:
      setRotor();
      break;
    case 6:
      changeSeed();
      break;
    default:
      break;
  }

}

