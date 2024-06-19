#include <iostream>
#include <string>
using namespace std;

class Gate {
 public:
  Gate* input[2];
  virtual bool output() = 0;
  void setValue(Gate*, int);
  void setValue(bool, int);
};

class TRUE : public Gate {
 public:
  virtual bool output() { return 1; }
  void setValue(Gate*, int) {}
  void setValue(bool, int) {}
};

class FALSE : public Gate {
 public:
  virtual bool output() { return 0; }
  void setValue(Gate*, int) {}
  void setValue(bool, int) {}
};

TRUE t;
FALSE f;

void Gate::setValue(bool val, int pin) {
  if (val)
    this->input[pin] = &t;
  else
    this->input[pin] = &f;
}

void Gate::setValue(Gate* gate, int pin) { this->input[pin] = gate; }

class NOT : public Gate {
 public:
  virtual bool output() { return !(this->input[0]->output()); }
  void setValue(bool val, int pin = 0) {
    if (val)
      this->input[0] = &t;
    else
      this->input[0] = &f;
  }
  void setValue(Gate* gate, int pin = 0) { this->input[0] = gate; }
};

class NAND : public Gate {
 public:
  virtual bool output() {
    return !(this->input[0]->output()) || !(this->input[1]->output());
  }
};

class NOR : public Gate {
 public:
  virtual bool output() {
    return !(this->input[0]->output()) && !(this->input[1]->output());
  }
};

class AND : public Gate {
 public:
  AND() : Gate() {
    component[0] = new NOT;
    component[1] = new NAND;
  }
  virtual bool output() {
    component[1]->input[0] = this->input[0];
    component[1]->input[1] = this->input[1];
    component[0]->input[0] = component[1];
    return component[0]->output();
  }

 private:
  Gate* component[2];
};

class OR : public Gate {
 public:
  OR() : Gate() {
    component[0] = new NOT;
    component[1] = new NOR;
  }
  virtual bool output() {
    component[1]->input[0] = this->input[0];
    component[1]->input[1] = this->input[1];
    component[0]->input[0] = component[1];
    return component[0]->output();
  }

 private:
  Gate* component[2];
};

class XOR : public Gate {
 public:
  XOR() : Gate() {
    component[0] = new OR;
    component[1] = new NAND;
  }
  virtual bool output() {
    component[0]->input[0] = this->input[0];
    component[0]->input[1] = this->input[1];
    component[1]->input[0] = this->input[0];
    component[1]->input[1] = this->input[1];
    return (component[0]->output() && component[1]->output());
  }

 private:
  Gate* component[2];
};

class Adder {
 public:
  virtual void setValue(bool, int) = 0;
  virtual void setValue(Gate*, int) = 0;
  virtual Gate* sum() = 0;
  virtual Gate* carryOut() = 0;
};

class OneBitHalfAdder : public Adder {
 public:
  OneBitHalfAdder() : Adder() {
    component[0] = new AND;
    component[1] = new XOR;
  }
  virtual void setValue(bool val, int pin) {
    component[0]->setValue(val, pin);
    component[1]->setValue(val, pin);
  }
  virtual void setValue(Gate* gate, int pin) {
    component[0]->setValue(gate, pin);
    component[1]->setValue(gate, pin);
  }
  virtual Gate* sum() { return component[1]; }
  virtual Gate* carryOut() { return component[0]; }

 private:
  Gate* component[2];
};

class OneBitFullAdder : public Adder {
 public:
  OneBitFullAdder() : Adder() {
    carry = new OR();
    a[0] = new OneBitHalfAdder();
    a[1] = new OneBitHalfAdder();
  }
  virtual void setValue(bool val, int pin) {
    if (pin < 2) {
      a[0]->setValue(val, pin);
    } else if (pin == 2) {
      a[1]->setValue(val, pin - 2);
    }
  }
  virtual void setValue(Gate* gate, int pin) {
    if (pin < 2) {
      a[0]->setValue(gate, pin);
    } else if (pin == 2) {
      a[1]->setValue(gate, pin - 2);
    }
  }
  virtual Gate* sum() {
    a[1]->setValue(a[0]->sum(), 1);
    return a[1]->sum();
  }
  virtual Gate* carryOut() {
    a[1]->setValue(a[0]->sum(), 1);
    carry->setValue(a[0]->carryOut(), 0);
    carry->setValue(a[1]->carryOut(), 1);

    return carry;
  }

 private:
  Adder* a[2];
  Gate* carry;
};

class Decoder {
 public:
  virtual void setValue(bool, int) = 0;
  virtual void setValue(Gate*, int) = 0;
  virtual void setEnable(bool) = 0;
  virtual void setEnable(Gate*) = 0;
  virtual int output() = 0;
  virtual Gate* operator[](int) = 0;

 protected:
  Gate* enable;
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
  virtual void setEnable(Gate* gate) { this->enable = gate; }
  virtual void setValue(Gate* gate, int i) {
    component[i % 2]->input[0] = gate;
  }
  virtual void setValue(bool val, int i) {
    if (val)
      component[i % 2]->input[0] = &t;
    else
      component[i % 2]->input[0] = &f;
  }
  virtual Gate* operator[](int n) {
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
  friend ostream& operator<<(ostream& out, Decoder2_4 dec) {
    for (int i = 3; i >= 0; i--) out << dec[i]->output() << " ";
    return out;
  }
  virtual int output() {
    for (int i = 0; i < 4; i++)
      if (enables[i]->output()) return i;
    return -1;
  }

 private:
  Gate* component[6];
  Gate* enables[4];

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
  virtual void setEnable(bool val) {
    if (val)
      dec2_4[4]->setEnable(true);
    else
      dec2_4[4]->setEnable(false);
  }
  virtual void setEnable(Gate* gate) { dec2_4[4]->setEnable(gate); }
  virtual void setValue(bool val, int pin) {
    if (pin < 2) {
      for (int i = 0; i < 4; i++) {
        dec2_4[i]->setValue(val, pin);
      }
    } else {
      dec2_4[4]->setValue(val, pin - 2);
    }
  }
  virtual void setValue(Gate* gate, int pin) {
    if (pin < 2) {
      for (int i = 0; i < 4; i++) {
        dec2_4[i]->setValue(gate, pin);
      }
    } else {
      dec2_4[4]->setValue(gate, pin - 2);
    }
  }
  virtual Gate* operator[](int n) { return (*dec2_4[n / 4])[n % 4]; }
  void refresh_dec() {
    for (int i = 0; i < 4; i++) {
      if ((*dec2_4[4])[i]->output())
        dec2_4[i]->setEnable(true);
      else
        dec2_4[i]->setEnable(false);
    }
  }
  friend ostream& operator<<(ostream& out, Decoder4_16 dec) {
    dec.refresh_dec();
    for (int i = 15; i >= 0; i--) {
      out << dec[i]->output() << " ";
    }
    return out;
  }
  virtual int output() {
    for (int i = 0; i < 16; i++)
      if ((*this)[i]->output()) return i;
    return -1;
  }

 private:
  Decoder* dec2_4[5];
};

class FourBitsRippleAdder : public Adder {
 public:
  FourBitsRippleAdder() {
    for (int i = 0; i < 4; i++) {
      a[i] = new OneBitFullAdder();
    }
    a[0]->setValue(false, 2);
  }
  virtual void setValue(bool val, int pin) {
    a[pin / 2]->setValue(val, (pin) % 2);
  }
  virtual void setValue(Gate* gate, int pin) {
    a[pin / 2]->setValue(gate, (pin) % 2);
  }
  virtual Gate* sum() {
    for (int i = 0; i < 3; i++) {
      a[i + 1]->setValue(a[i]->carryOut(), 2);
    }
    return a[3]->sum();
  }
  virtual Gate* carryOut() {
    for (int i = 0; i < 3; i++) {
      a[i + 1]->setValue(a[i]->carryOut(), 2);
    }
    return a[3]->carryOut();
  }
  Gate* get_dec_sum(int i) { return a[i]->sum(); }

 private:
  OneBitFullAdder* a[4];
};

class Decoder5_32 : public Decoder {
 public:
  Decoder5_32() : Decoder5_32(0) {}
  Decoder5_32(bool val) {
    dec4_16[0] = new Decoder4_16;
    dec4_16[1] = new Decoder4_16;
  }
  virtual void setEnable(bool val) {
    if (val)
      this->setEnable(true);
    else
      this->setEnable(false);
  }
  virtual void setEnable(Gate* gate) {
    if (gate)
      this->setEnable(true);
    else
      this->setEnable(false);
  }
  virtual void setValue(bool val, int pin) {
    dec4_16[0]->setValue(val, pin);
    dec4_16[1]->setValue(val, pin);
  }
  virtual void setValue(Gate* gate, int pin) {
    dec4_16[0]->setValue(gate, pin);
    dec4_16[1]->setValue(gate, pin);
  }
  virtual Gate* operator[](int n) { return (*dec4_16[n / 16])[n % 4]; }
  friend ostream& operator<<(ostream& out, Decoder5_32 dec) {
    out << (*dec.dec4_16[1]) << (*dec.dec4_16[0]);
    return out;
  }
  virtual int output() {
    if (dec4_16[0]->output() >= 0)
      return dec4_16[0]->output();
    else if (dec4_16[1]->output() >= 0)
      return dec4_16[1]->output() + 16;
    return -1;
  }
  void set_dec_enable(Gate* gate) {
    dec4_16[0]->setEnable(!(gate->output()));
    dec4_16[1]->setEnable(gate);
  }

 private:
  Decoder4_16* dec4_16[2];
};

int main() {
  bool in;
  Gate* head;
  FourBitsRippleAdder* fbra = new FourBitsRippleAdder();
  Decoder5_32 dec;
  for (int i = 6; i >= 0; i -= 2) {
    cin >> in;
    fbra->setValue(in, i);
  }
  for (int i = 7; i > 0; i -= 2) {
    cin >> in;
    fbra->setValue(in, i);
  }
  dec.set_dec_enable(fbra->carryOut());
  for (int i = 0; i < 4; i++) {
    dec.setValue(fbra->get_dec_sum(i), i);
  }
  cout << dec << endl;
  cout << dec.output();
}