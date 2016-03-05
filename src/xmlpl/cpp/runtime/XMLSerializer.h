/*******************************************************************\

              Copyright (C) 2003 Joseph Coffland

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


#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include "dom/String.h"

#include <map>

namespace xmlpl {

	/** 
	 * A XML serializer interface similar to SAX but in reverse.
	 */
	class XMLSerializer {

	public:
		virtual ~XMLSerializer() {}

		/**
		 * The element attribute type definition.  This is just a
		 * std::map.  You can create attributes as follows:
		 * 
		 * XMLSerializer::attributes_t attrs;<br>
		 * attrs["anAttribute"] = "aValue";
		 */
		typedef std::map<const String, String> attributes_t;


		/** 
		 * Start the XML document.
		 */
		virtual void startDocument() = 0;

		/** 
		 * Start an element.
		 * 
		 * @param qname The fully qualified element name.
		 * @param attributes The elements attributes.
		 */
		virtual void startElement(const String qname, 
															attributes_t &attributes) = 0;

		/** 
		 * Start an attributeless element.
		 * 
		 * @param qname The fully qualified element name.
		 */
		virtual void startElement(const String qname) = 0;

		/** 
		 * Output character data.  This data will be escaped if
		 * isEscaping() is true.  If you call setEscaping(false) and
		 * use this function there is no garuntee that your XML
		 * will be well-formed.  If you print characters such as <, >,
		 * or & it will likely be invalid.
		 * 
		 * @param text The text to print.
		 */
		virtual void characters(const String text) = 0;

		/** 
		 * Close an element.  XMLSerializer implementations must
		 * remember the name of the element be closed.
		 */
		virtual void endElement() = 0;

		/** 
		 * End the XML document.  Subsequent calls to startElement,
		 * endElement, characters, etc. will throw BasicExceptions.
		 */
		virtual void endDocument() = 0;

		/** 
		 * Output an XML comment.  These are of the format <!-- text -->
		 * 
		 * @param text The comment text.
		 */
		virtual void comment(const String text) = 0;

		/** 
		 * Output an XML processing instruction.
		 */
		virtual void processingInstruction(const String target, 
																			 const String data) = 0;

		/** 
		 * Flush the output buffer.
		 */
		virtual void flush() = 0;

		/** 
		 * Close the output buffer.
		 */
		virtual void close() = 0;


		/// @return an instance of the default XMLSerializer
		static XMLSerializer *createInstance(std::ostream &out);
	};
};

#endif
