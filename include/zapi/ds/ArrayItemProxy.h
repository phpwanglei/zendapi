// @copyright 2017-2018 zzu_softboy <zzu_softboy@163.com>
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Created by softboy on 2017/08/15.

#ifndef ZAPI_DS_INTERNAL_ARRAY_ITEM_PROXY_H
#define ZAPI_DS_INTERNAL_ARRAY_ITEM_PROXY_H

#include "zapi/Global.h"

// forward declare with namespace
namespace zapi
{
namespace ds
{
namespace internal
{
class ArrayItemProxyPrivate;
} // internal

class ArrayItemProxy;
class Variant;
class NumericVariant;
class DoubleVariant;
class StringVariant;
class BoolVariant;
class ArrayVariant;
using internal::ArrayItemProxyPrivate;
using zapi::lang::Type;

} // ds

extern bool array_unset(ds::ArrayItemProxy &&arrayItem);
extern bool array_isset(ds::ArrayItemProxy &&arrayItem);

} // zapi
// end forward declare

namespace zapi
{
namespace ds
{

class ZAPI_DECL_EXPORT ArrayItemProxy final
{
public:
   using KeyType = std::pair<zapi_ulong, std::shared_ptr<std::string>>;
public:
   ArrayItemProxy(zval *array, const KeyType &requestKey, ArrayItemProxy *parent = nullptr);
   ArrayItemProxy(zval *array, const std::string &key, ArrayItemProxy *parent = nullptr);
   ArrayItemProxy(zval *array, zapi_ulong index, ArrayItemProxy *parent = nullptr);
   ArrayItemProxy(const ArrayItemProxy &other); // shadow copy
   ArrayItemProxy(ArrayItemProxy &&other) ZAPI_DECL_NOEXCEPT;
   ~ArrayItemProxy();
   // operators
   ArrayItemProxy &operator =(const ArrayItemProxy &other);
   ArrayItemProxy &operator =(ArrayItemProxy &&other) ZAPI_DECL_NOEXCEPT;
   ArrayItemProxy &operator =(const Variant &value);
   ArrayItemProxy &operator =(const NumericVariant &value);
   ArrayItemProxy &operator =(const DoubleVariant &value);
   ArrayItemProxy &operator =(const StringVariant &value);
   ArrayItemProxy &operator =(const BoolVariant &value);
   ArrayItemProxy &operator =(const ArrayVariant &value);
   
   ArrayItemProxy &operator =(NumericVariant &&value);
   ArrayItemProxy &operator =(DoubleVariant &&value);
   ArrayItemProxy &operator =(StringVariant &&value);
   ArrayItemProxy &operator =(BoolVariant &&value);
   ArrayItemProxy &operator =(ArrayVariant &&value);
   
   ArrayItemProxy &operator =(const char *value);
   ArrayItemProxy &operator =(const char value);
   ArrayItemProxy &operator =(const std::string &value);
   template <typename T,
             typename Selector = typename std::enable_if<std::is_arithmetic<T>::value>::type>
   ArrayItemProxy &operator =(T value);
   template <size_t arrayLength>
   ArrayItemProxy &operator =(char (&value)[arrayLength]);
   // cast operators
   operator Variant();
   operator NumericVariant();
   operator DoubleVariant();
   operator StringVariant();
   operator BoolVariant();
   operator ArrayVariant();
   Variant toVariant();
   NumericVariant toNumericVariant();
   DoubleVariant toDoubleVariant();
   StringVariant toStringVariant();
   BoolVariant toBoolVariant();
   ArrayVariant toArrayVariant();
   // nest assign
   ArrayItemProxy operator [](zapi_long index);
   ArrayItemProxy operator [](const std::string &key);
protected:
   bool ensureArrayExistRecusive(zval *&childArrayPtr, const KeyType &childRequestKey,
                                 ArrayItemProxy *mostDerivedProxy);
   void checkExistRecursive(bool &stop, zval *&checkExistRecursive, 
                            ArrayItemProxy *mostDerivedProxy, bool quiet = false);
   bool isKeychianOk(bool quiet = false);
   zval *retrieveZvalPtr(bool quiet = false) const;
protected:
   friend bool zapi::array_unset(ArrayItemProxy &&arrayItem);
   friend bool zapi::array_isset(ds::ArrayItemProxy &&arrayItem);
   ZAPI_DECLARE_PRIVATE(ArrayItemProxy)
   std::shared_ptr<ArrayItemProxyPrivate> m_implPtr;
};

template <typename T, typename Selector>
ArrayItemProxy &ArrayItemProxy::operator =(T value)
{
   return operator =(Variant(value));
}

template <size_t arrayLength>
ArrayItemProxy &ArrayItemProxy::operator =(char (&value)[arrayLength])
{
   return operator =(Variant(value));
}

} // ds
} // zapi

#endif // ZAPI_DS_INTERNAL_ARRAY_ITEM_PROXY_H