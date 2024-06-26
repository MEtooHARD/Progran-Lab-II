#include <iostream>
#include <ostream>

using namespace std;

class Gate {
 public:
  Gate *input[2];
  virtual bool output() = 0;
  /* virtual */ void setValue(Gate *, int) /* = 0 */;
  /* virtual */ void setValue(bool, int) /* = 0 */;
};

class TRUE : public Gate {
 public:
  bool output() { return 1; }
  virtual void setValue(Gate *, int) {}
  virtual void setValue(bool, int) {}
};

class FALSE : public Gate {
 public:
  bool output() { return 0; }
  virtual void setValue(Gate *, int) {}
  virtual void setValue(bool, int) {}
};

TRUE t;
FALSE f;

void Gate::setValue(bool val, int pin) {
  if (val)
    this->input[pin] = &t;
  else
    this->input[pin] = &f;
}

void Gate::setValue(Gate *gate, int pin) { this->input[pin] = gate; }

class NOT : public Gate {
 public:
  bool output() { return !(this->input[0]->output()); }
  virtual void setValue(bool val, int pin = 0) {
    if (val)
      this->input[0] = &t;
    else
      this->input[0] = &f;
  }
  virtual void setValue(Gate *gate, int pin = 0) { this->input[0] = gate; }
};

class NAND : public Gate {
 public:
  bool output() {
    return !(this->input[0]->output()) || !(this->input[1]->output());
  }
  virtual void setValue(Gate *gate, int pin) { this->input[pin] = gate; }
  virtual void setValue(bool val, int pin) {
    if (val)
      setValue(&t, pin);
    else
      setValue(&f, pin);
  }
};

class NOR : public Gate {
 public:
  bool output() {
    return !(this->input[0]->output()) && !(this->input[1]->output());
  }
  virtual void setValue(Gate *gate, int pin) { this->input[pin] = gate; }
  virtual void setValue(bool val, int pin) {
    if (val)
      setValue(&t, pin);
    else
      setValue(&f, pin);
  }
};

class AND : public Gate {
 public:
  AND() : Gate() {
    component[0] = new NAND();
    component[1] = new NOT();
  }
  virtual bool output() {
    component[0]->setValue(input[0], 0);
    component[0]->setValue(input[1], 1);
    component[1]->setValue(component[0]->output(), 0);
    return component[1]->output();
  }

 private:
  Gate *component[2];
};

class OR : public Gate {
 public:
  OR() : Gate() {
    component[0] = new NOR();
    component[1] = new NOT();
  }
  virtual bool output() {
    component[0]->setValue(input[0], 0);
    component[0]->setValue(input[1], 1);
    component[1]->setValue(component[0]->output(), 0);
    return component[1]->output();
  }

 private:
  Gate *component[2];
};

class XOR : public Gate {
 public:
  XOR() : Gate() {
    component[0] = new OR();
    component[1] = new NAND();
    component[2] = new AND();
  }
  virtual bool output() {
    component[0]->setValue(input[0], 0);
    component[0]->setValue(input[1], 1);
    component[1]->setValue(input[0], 0);
    component[1]->setValue(input[1], 1);
    component[2]->setValue(component[0]->output(), 0);
    component[2]->setValue(component[1]->output(), 1);
    return component[2]->output();
  }

 private:
  Gate *component[5];
};

class Decoder {
 public:
  virtual void setValue(bool, int) = 0;
  virtual void setValue(Gate *, int) = 0;
  virtual void setEnable(bool) = 0;
  virtual void setEnable(Gate *) = 0;
  virtual int output() = 0;
  virtual Gate *operator[](int) = 0;

 protected:
  Gate *enable;
};

class Decoder2_4 : public Decoder {
 public:
  Decoder2_4() : Decoder2_4(0) {}
  Decoder2_4(bool val) {
    if (val)
      this->enable = &t;
    else
      this->enable = &f;
    for (int i = 0; i < 2; i++) component[i] = new NOT;
    for (int i = 2; i < 6; i++) component[i] = new AND;
    for (int i = 0; i < 4; i++) enables[i] = new AND;
  }
  virtual void setEnable(bool val) {
    if (val)
      this->enable = &t;
    else
      this->enable = &f;
  }
  virtual void setEnable(Gate *gate) { this->enable = gate; }
  virtual void setValue(Gate *gate, int i) {
    component[i % 2]->input[0] = gate;
  }
  virtual void setValue(bool val, int i) {
    if (val)
      component[i % 2]->input[0] = &t;
    else
      component[i % 2]->input[0] = &f;
  }
  virtual Gate *operator[](int n) {
    _out();
    switch (n) {
      case 0:
        return enables[0];
      case 1:
        return enables[1];
      case 2:
        return enables[2];
      case 3:
        return enables[3];
      default:
        return nullptr;
    }
  }
  friend ostream &operator<<(ostream &out, Decoder2_4 dec) {
    for (int i = 3; i >= 0; i--) out << dec[i]->output() << " ";
    return out;
  }
  virtual int output() {
    for (int i = 0; i < 4; i++)
      if (enables[i]->output()) return i;
  }

 private:
  Gate *component[6];
  Gate *enables[4];

  void _out() {
    component[2]->input[0] = component[0];
    component[2]->input[1] = component[1];

    component[3]->input[0] = component[0]->input[0];
    component[3]->input[1] = component[1];

    component[4]->input[0] = component[0];
    component[4]->input[1] = component[1]->input[0];

    component[5]->input[0] = component[0]->input[0];
    component[5]->input[1] = component[1]->input[0];

    for (int i = 0; i < 4; i++) {
      enables[i]->input[0] = this->enable;
      enables[i]->input[1] = component[i + 2];
    }
  }
};

class Decoder4_16 : public Decoder {
 public:
  Decoder4_16() : Decoder4_16(0) {}
  Decoder4_16(bool val) {
    for (int i = 0; i < 5; i++) {
      dec2_4[i] = new Decoder2_4;
    }
    if (val)
      dec2_4[4]->setEnable(true);
    else
      dec2_4[4]->setEnable(false);
  }
  virtual void setEnable(Gate *gate) { this->enable = gate; }
  virtual void setValue(bool val, int pin) {
    switch (pin) {
      case 0:
      case 1:
        for (int i = 1; i < 5; i++) dec2_4[i]->setValue(val, pin);
        break;
      case 2:
      case 3:
        dec2_4[0]->setValue(val, pin - 2);
    }
  }
  virtual void setValue(Gate *gate, int pin) {
    switch (pin) {
      case 0:
      case 1:
        for (int i = 1; i < 5; i++) dec2_4[i]->setValue(gate, pin);
        break;
      case 2:
      case 3:
        dec2_4[0]->setValue(gate, pin);
    }
  }
  virtual Gate *operator[](int n) {
    dec2_4[n / 4 + 1]->setEnable((*dec2_4[0])[n / 4]->output());
    return (*dec2_4[n / 4 + 1])[n / 4];
  }
  friend ostream &operator<<(ostream &out, Decoder4_16 dec) {
    for (int i = 15; i >= 0; i--) out << dec[i]->output() << " ";
    return out;
  }
  int output() {
    for (int i = 0; i < 16; i++)
      if ((*this)[i]->output()) return i;
    return -1;
  }

 private:
  Decoder *dec2_4[5];
};

/* int main() {
  Decoder4_16 *dec = new Decoder4_16();
  for (int i = 0; i < 4; i++) dec->setValue(true, i);
  cout << *dec;
} */