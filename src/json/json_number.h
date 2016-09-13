#ifndef NUMBER_H
#define NUMBER_H

#include "json_value.h"
#include "json_json.h"

#define DOUBLE 0
#define EXP 1

#define START 0
#define END 1

#ifdef UNIT_TEST
class json_number_test;
#endif

/**
 * @brief The number class
 */
class Number : public Value
{
#ifdef UNIT_TEST
friend class json_number_test;
#endif

public:

  Number ()
  : Value::Value (),
    _double_value (0),
    _double_valuep (&_double_value),
    _digitp {{ 0, 0 },{ 0, 0 }}
  {
  }

  explicit Number (const double value)
    : Value::Value (),
      _double_value (value),
      _double_valuep (&_double_value),
      _digitp {{ 0, 0 },{ 0, 0 }}
  {
  }

  Number (const char *json)
    : Value::Value (json),
      _double_value (0),
      _double_valuep (0),
      _digitp {{ 0, 0 },{ 0, 0 }}
  {
    if (_length == 0)
      throw JSON::error ("null string");

    (void) parse (json);
  }

  Number (JSON *parent)
    : Value::Value (parent),
      _double_value (0),
      _double_valuep (0),
      _digitp {{ 0, 0 },{ 0, 0 }}
  {
  }

  virtual ~Number () {}

  /**
   * @brief parse
   * @param json
   * @return
   */
  virtual const char *parse (const char *json);

  /**
   * @brief at
   * @param key
   * @return
   */
  virtual inline Value & at (const char *) { return *this; }

  /**
   * @brief type
   * @return
   */
  virtual inline object_type type () const { return Value::object_type::number; }

  /**
   * @brief size
   * @return
   */
  virtual inline size_t size () const { return _double_valuep == 0 ? 0 : 1; }


  virtual Value & assign (Value & nv) { return Value::assign (nv); }

  Value & assign (Number & nv);

  /**
   * @brief value
   * @return
   */
  inline double value () { return _double_valuep == 0 ?  _calculate (_digitp) : _double_value; }

protected:

  virtual inline Value &_at (const char *) { return *this; }

protected:

  /**
   * @brief _value
   */
  double _double_value;

  /**
   * @brief _double_valuep
   */
  double *_double_valuep;

  /**
   * @brief _digitp
   */
  const char *_digitp[2][2];

  /**
   * @brief _double_string
   */
  std::string _digit_string;

  /**
   * @brief _digits If >= 1 digits found, return last character. Else return -1.
   * @return
   */
  int _digits ();

  /**
   * @brief _frag
   * @return
   */
  const char * _frag ();

  /**
   * @brief _exp_
   * @return
   */
  const char * _exp ();

  /**
   * @brief _calculate
   * @param digitp
   * @return
   */
  double _calculate (const char * const digitp[2][2]);

  /**
   * @brief _atof
   * @param digitp
   * @return
   */
  double _atof (const char * const digitp[2]);

  /**
   * @brief _atoll
   * @param digitp
   * @return
   */
  long long _atoll (const char * const digitp[2]);
};

#endif // NUMBER_H
