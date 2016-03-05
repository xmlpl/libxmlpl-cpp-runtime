#ifndef COMMENT_H
#define COMMENT_H

#include "Node.h"

namespace xmlpl {
  class Comment;
  typedef Reference<Comment, Node> CommentRef;

  class Comment: public Node {
    const String text;

  public:
    Comment(const String &text) : text(text) {}
    virtual ~Comment() {}

    virtual const unsigned int getType() const {return COMMENT_TYPE;}
    Node *clone() const {return new Comment(text);}

    virtual const String &getText() const {return text;}

    virtual void serialize(XMLStream &stream) {stream.comment(getText());}
  };
};
#endif
