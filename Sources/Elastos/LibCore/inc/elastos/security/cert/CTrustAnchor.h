//=========================================================================
// Copyright (C) 2012 The Elastos Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=========================================================================

#ifndef __ELASTOS_SECURITY_CERT_CTRUSTANCHOR_H__
#define __ELASTOS_SECURITY_CERT_CTRUSTANCHOR_H__

#include "_Elastos_Security_Cert_CTrustAnchor.h"
#include "Elastos.CoreLibrary.Extensions.h"
#include "core/Object.h"

using Elastosx::Security::Auth::X500::IX500Principal;
using Elastos::Security::IPublicKey;

namespace Elastos {
namespace Security {
namespace Cert {

CarClass(CTrustAnchor)
    , public Object
    , public ITrustAnchor
{
public:
    CAR_OBJECT_DECL()

    CAR_INTERFACE_DECL()

    CARAPI GetNameConstraints(
        /* [out, callee] */ ArrayOf<Byte> **nameConstraints);

    CARAPI GetTrustedCert(
        /* [out] */ IX509Certificate **cert);

    CARAPI GetCA(
        /* [out] */ IX500Principal **ca);

    CARAPI GetCAName(
        /* [out] */ String *caName);

    CARAPI GetCAPublicKey(
        /* [out] */ IPublicKey **key);

    CARAPI ToString(
        /* [out] */ String *str);

    CARAPI constructor(
        /* [in] */ IX509Certificate *trustedCert,
        /* [in] */ ArrayOf<Byte> *nameConstraints);

    CARAPI constructor(
        /* [in] */ const String& caName,
        /* [in] */ IPublicKey *caPublicKey,
        /* [in] */ ArrayOf<Byte> *nameConstraints);

    CARAPI constructor(
        /* [in] */ IX500Principal *caPrincipal,
        /* [in] */ IPublicKey *caPublicKey,
        /* [in] */ ArrayOf<Byte> *nameConstraints);

private:
    // Decodes and checks NameConstraints structure.
    // Throws IllegalArgumentException if NameConstraints
    // encoding is invalid.
    CARAPI ProcessNameConstraints();

private:
    // Most trusted CA as a X500Principal
    AutoPtr<IX500Principal> mCaPrincipal;
    // Most trusted CA name
    String mCaName;
    // Most trusted CA public key
    AutoPtr<IPublicKey> mCaPublicKey;
    // Most trusted CA certificate
    AutoPtr<IX509Certificate> mTrustedCert;
    // Name constraints extension
    AutoPtr<ArrayOf<Byte> > mNameConstraints;
};

}
}
}

#endif // __ELASTOS_SECURITY_CERT_CTRUSTANCHOR_H__
