#ifndef TYPEID_H
#define TYPEID_H

namespace xmlpl {
  class TypeID {
  public:
    // WARNING: Changes to type values must also be made in the macro from
    //          the OpenOffice spreadsheet xmlpl/Parser/Environment/XmlPLTypeTables.sxc
    //          and TypeTables.{cpp,h} must be regenerated from this macro.
    //          New built-in types must be added here, to the spreadsheet and
    //          its macro and the tables regenerated.
    enum {
      UNKNOWN_TYPE       = 0,
      RESERVED_TYPE      = 1,
      
      VOID_TYPE          = 2,
      NULL_TYPE          = 3,

      BOOLEAN_TYPE       = 4,
      INTEGER_TYPE       = 5,
      REAL_TYPE          = 6,
      STRING_TYPE        = 7,
      PREFIX_TYPE        = 8,
      QNAME_TYPE         = 9,
      EXCEPTION_TYPE     = 10,

      PROXY_TYPE         = 11,

      // Node types
      NODE_FLAG          = 16,
      NODE_TYPE          = 0 | NODE_FLAG,

      DOCUMENT_TYPE      = 1 | NODE_FLAG,
      ELEMENT_TYPE       = 2 | NODE_FLAG,
      ATTRIBUTE_TYPE     = 3 | NODE_FLAG,
      TEXT_TYPE          = 4 | NODE_FLAG,
      COMMENT_TYPE       = 5 | NODE_FLAG,
      PI_TYPE            = 6 | NODE_FLAG,


      // Sequence types
      SEQUENCE_FLAG      = 32,

      BOOLEAN_SEQ_TYPE   = BOOLEAN_TYPE   | SEQUENCE_FLAG,
      INTEGER_SEQ_TYPE   = INTEGER_TYPE   | SEQUENCE_FLAG,
      REAL_SEQ_TYPE      = REAL_TYPE      | SEQUENCE_FLAG,
      STRING_SEQ_TYPE    = STRING_TYPE    | SEQUENCE_FLAG,
      PREFIX_SEQ_TYPE    = PREFIX_TYPE    | SEQUENCE_FLAG,
      QNAME_SEQ_TYPE     = QNAME_TYPE     | SEQUENCE_FLAG,

      NODE_SEQ_TYPE      = NODE_TYPE      | SEQUENCE_FLAG,

      DOCUMENT_SEQ_TYPE  = DOCUMENT_TYPE  | SEQUENCE_FLAG,
      ELEMENT_SEQ_TYPE   = ELEMENT_TYPE   | SEQUENCE_FLAG,
      ATTRIBUTE_SEQ_TYPE = ATTRIBUTE_TYPE | SEQUENCE_FLAG,
      TEXT_SEQ_TYPE      = TEXT_TYPE      | SEQUENCE_FLAG,
      COMMENT_SEQ_TYPE   = COMMENT_TYPE   | SEQUENCE_FLAG,
      PI_SEQ_TYPE        = PI_TYPE        | SEQUENCE_FLAG,

      // Iterator types
      ITERATOR_FLAG       = 64,

      BOOLEAN_ITER_TYPE   = BOOLEAN_TYPE   | ITERATOR_FLAG,
      INTEGER_ITER_TYPE   = INTEGER_TYPE   | ITERATOR_FLAG,
      REAL_ITER_TYPE      = REAL_TYPE      | ITERATOR_FLAG,
      STRING_ITER_TYPE    = STRING_TYPE    | ITERATOR_FLAG,
      PREFIX_ITER_TYPE    = PREFIX_TYPE    | ITERATOR_FLAG,
      QNAME_ITER_TYPE     = QNAME_TYPE     | ITERATOR_FLAG,

      NODE_ITER_TYPE      = NODE_TYPE      | ITERATOR_FLAG,

      DOCUMENT_ITER_TYPE  = DOCUMENT_TYPE  | ITERATOR_FLAG,
      ELEMENT_ITER_TYPE   = ELEMENT_TYPE   | ITERATOR_FLAG,
      ATTRIBUTE_ITER_TYPE = ATTRIBUTE_TYPE | ITERATOR_FLAG,
      TEXT_ITER_TYPE      = TEXT_TYPE      | ITERATOR_FLAG,
      COMMENT_ITER_TYPE   = COMMENT_TYPE   | ITERATOR_FLAG,
      PI_ITER_TYPE        = PI_TYPE        | ITERATOR_FLAG,

      // OStream types
      OSTREAM_FLAG      = 128,

      BOOLEAN_OSTR_TYPE   = BOOLEAN_TYPE   | OSTREAM_FLAG,
      INTEGER_OSTR_TYPE   = INTEGER_TYPE   | OSTREAM_FLAG,
      REAL_OSTR_TYPE      = REAL_TYPE      | OSTREAM_FLAG,
      STRING_OSTR_TYPE    = STRING_TYPE    | OSTREAM_FLAG,
      PREFIX_OSTR_TYPE    = PREFIX_TYPE    | OSTREAM_FLAG,
      QNAME_OSTR_TYPE     = QNAME_TYPE     | OSTREAM_FLAG,

      NODE_OSTR_TYPE      = NODE_TYPE      | OSTREAM_FLAG,

      DOCUMENT_OSTR_TYPE  = DOCUMENT_TYPE  | OSTREAM_FLAG,
      ELEMENT_OSTR_TYPE   = ELEMENT_TYPE   | OSTREAM_FLAG,
      ATTRIBUTE_OSTR_TYPE = ATTRIBUTE_TYPE | OSTREAM_FLAG,
      TEXT_OSTR_TYPE      = TEXT_TYPE      | OSTREAM_FLAG,
      COMMENT_OSTR_TYPE   = COMMENT_TYPE   | OSTREAM_FLAG,
      PI_OSTR_TYPE        = PI_TYPE        | OSTREAM_FLAG
    };
  };
};
#endif //TYPEID_H
