/*******************************************************************\

              Copyright (C) 2006 Joseph Coffland

    This program is free software; you can redistribute it and/or
     modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
        of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
             GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
     along with this program; if not, write to the Free Software
      Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
                           02111-1307, USA.

            For information regarding this software email
                   jcofflan@users.sourceforge.net

\*******************************************************************/


#ifndef XMLSTREAM2SERIALIZERADAPTER_H
#define XMLSTREAM2SERIALIZERADAPTER_H

#include "XMLSerializer.h"
#include "dom/XMLStream.h"
#include "Memory.h"

namespace xmlpl {

	/** 
	 * A XML serializer interface similar to SAX but in reverse.
	 */
	class XMLStream2SerializerAdapter :
		public virtual Memory, public XMLSerializer {
		XMLStream *stream;
		
	public:
		XMLStream2SerializerAdapter(XMLStream *stream);
		virtual ~XMLStream2SerializerAdapter() {}
		
		virtual void startDocument();
		virtual void startElement(const String qname, 
															attributes_t &attributes);
		virtual void startElement(const String qname);
		virtual void characters(const String text);
		virtual void endElement();
		virtual void endDocument();
		virtual void comment(const String text);
		virtual void processingInstruction(const String target, 
																			 const String data);
		
		virtual void flush();
		virtual void close();
	};
};

#endif
