uint8_t cambien[11] = { A0, A1, A2, A3, A4, A5, A6, A7, 3, 4, 11 };

#define dct1 5  // động cơ bên trái tiền (1)
#define dct2 6  // động cơ bên trai lui (1)
#define dct 9   // tốc độ động cơ trái
#define dcp1 7  //động cơ bên phải tiền (1)
#define dcp2 8  //động cơ bên phải lui (1)
#define dcp 10  //tốc độ động cơ phải
uint8_t cb[11], co = 0;

char danhdauduong[30], giatriphandoan;
int d1 = 0, d2 = 0;
int trangthai = 1;
const int TOCDO = 97;


void indongco() {
  pinMode(dcp1, OUTPUT);
  pinMode(dcp2, OUTPUT);
  pinMode(dcp, OUTPUT);
  pinMode(dct1, OUTPUT);
  pinMode(dct2, OUTPUT);
  pinMode(dct, OUTPUT);
}

void incambien() {
  digitalWrite(2, HIGH);
  pinMode(cambien[0], INPUT);
  pinMode(cambien[1], INPUT);
  pinMode(cambien[2], INPUT);
  pinMode(cambien[3], INPUT);
  pinMode(cambien[4], INPUT);
  pinMode(cambien[5], INPUT);
  pinMode(cambien[6], INPUT);
  pinMode(cambien[7], INPUT);
  pinMode(cambien[8], INPUT);
  pinMode(cambien[9], INPUT);
  pinMode(cambien[10], INPUT);
}

uint8_t digital(uint8_t x) {
  if (analogRead(x) > 890)
    return 1;
  else
    return 0;
}

void resetcb() {
  cb[9] = digitalRead(cambien[9]);
  cb[10] = digitalRead(cambien[10]);
  cb[8] = digitalRead(cambien[8]);
  cb[0] = digital(cambien[0]);
  cb[1] = digital(cambien[1]);
  cb[2] = digital(cambien[2]);
  cb[3] = digital(cambien[3]);
  cb[4] = digital(cambien[4]);
  cb[5] = digital(cambien[5]);
  cb[6] = digital(cambien[6]);
  cb[7] = digital(cambien[7]);
}

char phandoan() {
  resetcb();
  if (!cb[7] && !cb[6] && !cb[5] && !cb[4] && !cb[3] && !cb[2] && !cb[1] && !cb[0] && cb[9])
    return 's';
  if ((cb[8] && cb[10]) || (cb[7] && cb[6] && cb[5] && cb[4] && cb[3] && cb[2] && cb[1] && cb[0])) {
    resetcb();
    if (!cb[7] && !cb[6] && !cb[5] && !cb[4] && !cb[3] && !cb[2] && !cb[1] && !cb[0] && cb[9])
      return 's';
    dongco('h', TOCDO, TOCDO);
    delay(240);
    resetcb();
    if (cb[0] || cb[1] || cb[2] || cb[3] || cb[4] || cb[5] || cb[6] || cb[7] || cb[9])
      return 'f';
    else
      return 't';
  }
  if (cb[7] && cb[6] && cb[5] && cb[4] && !cb[1] && !cb[0]) {
    dongco('h', TOCDO, TOCDO);
    delay(170);
    resetcb();
    if (cb[0] || cb[1] || cb[2] || cb[3] || cb[4] || cb[5] || cb[6] || cb[7] || cb[9])
      return 'a';
    else
      return 'l';
  }
  if (cb[0] && cb[1] && cb[2] && cb[3] && !cb[6] && !cb[7]) {
    dongco('h', TOCDO, TOCDO);
    delay(170);
    resetcb();
    if (cb[0] || cb[1] || cb[2] || cb[3] || cb[4] || cb[5] || cb[6] || cb[7] || cb[9])
      return 'd';
    else
      return 'r';
  }
  if (!cb[7] && !cb[6] && !cb[5] && !cb[4] && !cb[3] && !cb[2] && !cb[1] && !cb[0] && !cb[8] && !cb[9] && !cb[10]) {
    dongco('h', TOCDO, TOCDO);
    delay(200);
    resetcb();
    if (!cb[7] && !cb[6] && !cb[5] && !cb[4] && !cb[3] && !cb[2] && !cb[1] && !cb[0] && !cb[8] && !cb[9] && !cb[10])
      return 'o';
  } else
    return 'h';  // theo line
}


char line() {
  if ((cb[0] || cb[1] || cb[2] || cb[3]) && !cb[4] && !cb[5] && !cb[6] && !cb[7])
    return 'r';
  else if (!cb[0] && !cb[1] && !cb[2] && cb[3] && cb[4] && !cb[5] && !cb[6] && !cb[7])
    return 'h';
  else if (!cb[0] && !cb[1] && !cb[2] && !cb[3] && (cb[4] || cb[5] || cb[6] || cb[7]))
    return 'l';
}

void dongcotrai(char x, unsigned int TOCDO) {
  switch (x) {
    case 'b':  // động cơ trái lui
      digitalWrite(dct1, HIGH);
      digitalWrite(dct2, LOW);
      analogWrite(dct, TOCDO);
      break;

    case 'h':  // động cơ trái tiến
      digitalWrite(dct1, LOW);
      digitalWrite(dct2, HIGH);
      analogWrite(dct, TOCDO);
      break;

    case 's':  // động cơ trái dừng
      digitalWrite(dct1, HIGH);
      digitalWrite(dct2, HIGH);
      analogWrite(dct, 0);
      break;
  }
}

void dongcophai(char x, unsigned int TOCDO) {
  switch (x) {
    case 'b':  // động cơ phải lui
      digitalWrite(dcp1, HIGH);
      digitalWrite(dcp2, LOW);
      analogWrite(dcp, TOCDO);
      break;


    case 'h':  // động cơ phải tiến
      digitalWrite(dcp1, LOW);
      digitalWrite(dcp2, HIGH);
      analogWrite(dcp, TOCDO);
      break;

    case 's':  // động cơ phải dừng
      digitalWrite(dcp1, HIGH);
      digitalWrite(dcp2, HIGH);
      analogWrite(dcp, 0);
      break;
  }
}

void dongco(char x, unsigned int tdt, unsigned int tdp) {
  switch (x) {
    case 's':  // xe dừng
      dongcophai('s', 0);
      dongcotrai('s', 0);
      break;


    case 'h':  // xe tiến
      dongcophai('h', tdp);
      dongcotrai('h', tdt);
      break;

    case 'l':  // xe quẹo trái
      dongcophai('h', tdp);
      dongcotrai('b', tdt);
      break;

    case 'r':  // xe quẹo phải
      dongcophai('b', tdp);
      dongcotrai('h', tdt);
      break;

    case 'b':  // xe lui
      dongcophai('b', tdp);
      dongcotrai('b', tdt);
      break;
  }
}

void theoline() {
  char l = line();
  switch (l) {
    case 'h':  // tiến
      dongco('h', TOCDO, TOCDO);
      break;

    case 'r':  // nhích phải
      dongco('r', TOCDO, 0);
      break;

    case 'l':  // nhích trái
      dongco('l', 0, TOCDO);
      break;

    case 's':  // dừng
      dongco('s', 0, 0);
      break;
  }
}

void hanhdong(char x) {
  switch (x) {
    case 'l':
      dongco('l', TOCDO, TOCDO);
      delay(300);
      do {
        dongco('l', TOCDO, TOCDO);
        resetcb();
      } while (!(cb[3] && cb[4]));
      break;

    case 'r':
      dongco('r', TOCDO, TOCDO);
      delay(350);
      do {
        dongco('r', TOCDO, TOCDO);
        resetcb();
      } while (!(cb[4] && cb[3]));
      break;

    case 'b':
      do {
        dongco('r', 120, 120);
        resetcb();
      } while (!(cb[3] && cb[4]));
      break;


    case 's':
      dongco('s', TOCDO, TOCDO);
      break;

    case 'h':
      theoline();
      break;
  }
}

char doihd(char x) {
  if (x == 'r')
    return 'l';
  else if (x == 'l')
    return 'r';
  else
    return x;
}

void rutngan(char x) {
  dongco('s', 0, 0);
  if (x == 'd') {
    if (co == 1)
      ++co;
    danhdauduong[d1] = 'h';
    d1++;
  } else if (x == 'o') {
    ++co;
    danhdauduong[d1] = 'b';
    d1++;
  } else {
    if (co == 1)
      ++co;
    danhdauduong[d1] = 'l';
    d1++;
  }
  if (co == 2) {
    if (danhdauduong[d1 - 3] == 'l') {
      if (danhdauduong[d1 - 1] == 'r') {
        danhdauduong[d1 - 3] = 'b';
        danhdauduong[d1 - 2] = '\0';
        danhdauduong[d1 - 1] = '\0';
        d1 += -2;
        co = 1;
      } else if (danhdauduong[d1 - 1] == 'h') {
        danhdauduong[d1 - 3] = 'r';
        danhdauduong[d1 - 2] = '\0';
        danhdauduong[d1 - 1] = '\0';
        d1 += -2;
        co = 0;
      } else if (danhdauduong[d1 - 1] == 'l') {
        danhdauduong[d1 - 3] = 'h';
        danhdauduong[d1 - 2] = '\0';
        danhdauduong[d1 - 1] = '\0';
        d1 += -2;
        co = 0;
      }
    } else if (danhdauduong[d1 - 3] == 'h') {
      if (danhdauduong[d1 - 1] == 'l') {
        danhdauduong[d1 - 3] = 'r';
        danhdauduong[d1 - 2] = '\0';
        danhdauduong[d1 - 1] = '\0';
        d1 += -2;
        co = 0;
      } else if (danhdauduong[d1 - 1] == 'h') {
        danhdauduong[d1 - 3] = 'b';
        danhdauduong[d1 - 2] = '\0';
        danhdauduong[d1 - 1] = '\0';
        d1 += -2;
        co = 1;
      }
    } else if (danhdauduong[d1 - 3] == 'r') {
      if (danhdauduong[d1 - 1] == 'l') {
        danhdauduong[d1 - 3] = 'b';
        danhdauduong[d1 - 2] = '\0';
        danhdauduong[d1 - 1] = '\0';
        d1 += -2;
        co = 1;
      }
    }
  }
}


void setup() {
  indongco();
  incambien();
}
void loop() {
  if (trangthai == 1) {
    giatriphandoan = phandoan();
    switch (giatriphandoan) {
      case 'l':
        hanhdong('l');
        break;

      case 'r':
        hanhdong('r');
        break;

      case 'a':
        rutngan('a');
        hanhdong('l');
        break;

      case 'd':
        rutngan('d');
        hanhdong('h');
        break;

      case 'f':
        rutngan('f');
        hanhdong('l');
        break;

      case 't':
        rutngan('t');
        hanhdong('l');
        break;

      case 'o':
        rutngan('o');
        hanhdong('b');
        break;

      case 's':
        trangthai++;
        hanhdong('s');
        d2 = d1 - 1;
        delay(3000);
        hanhdong('b');
        break;

      case 'h':
        theoline();
        break;
    }
  } else if (trangthai == 2) {
    giatriphandoan = phandoan();
    switch (giatriphandoan) {
      case 'l':
        hanhdong('l');
        break;

      case 'r':
        hanhdong('r');
        break;

      case 'a':
        hanhdong(doihd(danhdauduong[d2]));
        d2 -= 1;
        break;

      case 'd':
        hanhdong(doihd(danhdauduong[d2]));
        d2 -= 1;
        break;

      case 'f':
        hanhdong(doihd(danhdauduong[d2]));
        d2 -= 1;
        break;

      case 't':
        hanhdong(doihd(danhdauduong[d2]));
        d2 -= 1;
        break;

      case 'o':
        trangthai++;
        d2 = 0;
        hanhdong('s');
        delay(3000);
        hanhdong('b');
        break;

      case 'h':
        theoline();
        break;
    }
  } else if (trangthai == 3) {
    giatriphandoan = phandoan();
    switch (giatriphandoan) {
      case 'l':
        hanhdong('l');
        break;

      case 'r':
        hanhdong('r');
        break;

      case 'a':
        hanhdong(danhdauduong[d2]);
        ++d2;
        break;

      case 'd':
        hanhdong(danhdauduong[d2]);
        ++d2;
        break;

      case 'f':
        hanhdong(danhdauduong[d2]);
        ++d2;
        break;

      case 't':
        hanhdong(danhdauduong[d2]);
        ++d2;
        break;

      case 'o':
        hanhdong('b');
        break;

      case 's':
        trangthai++;
        hanhdong('s');
        break;

      case 'h':
        theoline();
        break;
    }
  } else {
    dongco('s', 0, 0);
  }
}