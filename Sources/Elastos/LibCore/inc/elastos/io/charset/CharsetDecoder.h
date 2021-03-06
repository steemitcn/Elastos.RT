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

#ifndef __ELASTOS_IO_CHARSET_CHARSETDECODER_H__
#define __ELASTOS_IO_CHARSET_CHARSETDECODER_H__

#include <elastos.h>

namespace Elastos {
namespace IO {
namespace Charset {

class CharsetDecoder
    : public Object
    , public ICharsetDecoder
{
public:
    CharsetDecoder();

    virtual ~CharsetDecoder();

    CAR_INTERFACE_DECL()

    /**
     * Constructs a new <code>CharsetDecoder</code> using the given
     * <code>Charset</code>, average number and maximum number of characters
     * created by this decoder for one input byte, and the default replacement
     * string "\uFFFD".
     *
     * @param charset
     *            the <code>Charset</code> to be used by this decoder.
     * @param averageCharsPerByte
     *            the average number of characters created by this decoder for
     *            one input byte, must be positive.
     * @param maxCharsPerByte
     *            the maximum number of characters created by this decoder for
     *            one input byte, must be positive.
     * @throws IllegalArgumentException
     *             if <code>averageCharsPerByte</code> or
     *             <code>maxCharsPerByte</code> is negative.
     */
    CARAPI constructor(
        /* [in] */ ICharset* charset,
        /* [in] */ Float averageCharsPerByte,
        /* [in] */ Float maxCharsPerByte);

    /**
     * Returns the average number of characters created by this decoder for a
     * single input byte.
     */
    CARAPI AverageCharsPerByte(
        /* [out] */ Float* average);

    /**
     * Returns the {@link Charset} which this decoder uses.
     */
    CARAPI Charset(
        /* [out] */ ICharset** charset);

    /**
     * This is a facade method for the decoding operation.
     * <p>
     * This method decodes the remaining byte sequence of the given byte buffer
     * into a new character buffer. This method performs a complete decoding
     * operation, resets at first, then decodes, and flushes at last.
     * <p>
     * This method should not be invoked while another {@code decode} operation
     * is ongoing.
     *
     * @param in
     *            the input buffer.
     * @return a new <code>CharBuffer</code> containing the the characters
     *         produced by this decoding operation. The buffer's limit will be
     *         the position of the last character in the buffer, and the
     *         position will be zero.
     * @throws IllegalStateException
     *             if another decoding operation is ongoing.
     * @throws MalformedInputException
     *             if an illegal input byte sequence for this charset was
     *             encountered, and the action for malformed error is
     *             {@link CodingErrorAction#REPORT CodingErrorAction.REPORT}
     * @throws UnmappableCharacterException
     *             if a legal but unmappable input byte sequence for this
     *             charset was encountered, and the action for unmappable
     *             character error is
     *             {@link CodingErrorAction#REPORT CodingErrorAction.REPORT}.
     *             Unmappable means the byte sequence at the input buffer's
     *             current position cannot be mapped to a Unicode character
     *             sequence.
     * @throws CharacterCodingException
     *             if another exception happened during the decode operation.
     */
    CARAPI Decode(
        /* [in] */ IByteBuffer* byteBuffer,
        /* [out] */ ICharBuffer** charBuffer);

    /**
     * Decodes bytes starting at the current position of the given input buffer,
     * and writes the equivalent character sequence into the given output buffer
     * from its current position.
     * <p>
     * The buffers' position will be changed with the reading and writing
     * operation, but their limits and marks will be kept intact.
     * <p>
     * A <code>CoderResult</code> instance will be returned according to
     * following rules:
     * <ul>
     * <li>{@link CoderResult#OVERFLOW CoderResult.OVERFLOW} indicates that
     * even though not all of the input has been processed, the buffer the
     * output is being written to has reached its capacity. In the event of this
     * code being returned this method should be called once more with an
     * <code>out</code> argument that has not already been filled.</li>
     * <li>{@link CoderResult#UNDERFLOW CoderResult.UNDERFLOW} indicates that
     * as many bytes as possible in the input buffer have been decoded. If there
     * is no further input and no remaining bytes in the input buffer then this
     * operation may be regarded as complete. Otherwise, this method should be
     * called once more with additional input.</li>
     * <li>A {@link CoderResult#malformedForLength(int) malformed input} result
     * indicates that some malformed input error has been encountered, and the
     * erroneous bytes start at the input buffer's position and their number can
     * be got by result's {@link CoderResult#length() length}. This kind of
     * result can be returned only if the malformed action is
     * {@link CodingErrorAction#REPORT CodingErrorAction.REPORT}. </li>
     * <li>A {@link CoderResult#unmappableForLength(int) unmappable character}
     * result indicates that some unmappable character error has been
     * encountered, and the erroneous bytes start at the input buffer's position
     * and their number can be got by result's
     * {@link CoderResult#length() length}. This kind of result can be returned
     * only if the unmappable character action is
     * {@link CodingErrorAction#REPORT CodingErrorAction.REPORT}. </li>
     * </ul>
     * <p>
     * The <code>endOfInput</code> parameter indicates that the invoker cannot
     * provide further input. This parameter is true if and only if the bytes in
     * current input buffer are all inputs for this decoding operation. Note
     * that it is common and won't cause an error if the invoker sets false and
     * then can't provide more input, while it may cause an error if the invoker
     * always sets true in several consecutive invocations. This would make the
     * remaining input to be treated as malformed input.
     * <p>
     * This method invokes the
     * {@link #decodeLoop(ByteBuffer, CharBuffer) decodeLoop} method to
     * implement the basic decode logic for a specific charset.
     *
     * @param in
     *            the input buffer.
     * @param out
     *            the output buffer.
     * @param endOfInput
     *            true if all the input characters have been provided.
     * @return a <code>CoderResult</code> instance which indicates the reason
     *         of termination.
     * @throws IllegalStateException
     *             if decoding has started or no more input is needed in this
     *             decoding progress.
     * @throws CoderMalfunctionError
     *             if the {@link #decodeLoop(ByteBuffer, CharBuffer) decodeLoop}
     *             method threw an <code>BufferUnderflowException</code> or
     *             <code>BufferOverflowException</code>.
     */
    CARAPI Decode(
        /* [in] */ IByteBuffer* byteBuffer,
        /* [in] */ ICharBuffer* charBuffer,
        /* [in] */ Boolean endOfInput,
        /* [out] */ ICoderResult** result);

    /**
     * Gets the charset detected by this decoder; this method is optional.
     * <p>
     * If implementing an auto-detecting charset, then this decoder returns the
     * detected charset from this method when it is available. The returned
     * charset will be the same for the rest of the decode operation.
     * <p>
     * If insufficient bytes have been read to determine the charset, an
     * <code>IllegalStateException</code> will be thrown.
     * <p>
     * The default implementation always throws
     * <code>UnsupportedOperationException</code>, so it should be overridden
     * by a subclass if needed.
     *
     * @return the charset detected by this decoder, or null if it is not yet
     *         determined.
     * @throws UnsupportedOperationException
     *             if this decoder does not implement an auto-detecting charset.
     * @throws IllegalStateException
     *             if insufficient bytes have been read to determine the
     *             charset.
     */
    CARAPI DetectedCharset(
        /* [out] */ ICharset** charset);

    /**
     * Flushes this decoder.
     *
     * This method will call {@link #implFlush(CharBuffer) implFlush}. Some
     * decoders may need to write some characters to the output buffer when they
     * have read all input bytes; subclasses can override
     * {@link #implFlush(CharBuffer) implFlush} to perform the writing operation.
     * <p>
     * The maximum number of written bytes won't be larger than
     * {@link CharBuffer#remaining() out.remaining()}. If some decoder wants to
     * write more bytes than an output buffer's remaining space allows, then a
     * <code>CoderResult.OVERFLOW</code> will be returned, and this method
     * must be called again with a character buffer that has more remaining
     * space. Otherwise this method will return
     * <code>CoderResult.UNDERFLOW</code>, which means one decoding process
     * has been completed successfully.
     * <p>
     * During the flush, the output buffer's position will be changed
     * accordingly, while its mark and limit will be intact.
     *
     * @param out
     *            the given output buffer.
     * @return <code>CoderResult.UNDERFLOW</code> or
     *         <code>CoderResult.OVERFLOW</code>.
     * @throws IllegalStateException
     *             if this decoder hasn't read all input bytes during one
     *             decoding process, which means neither after calling
     *             {@link #decode(ByteBuffer) decode(ByteBuffer)} nor after
     *             calling {@link #decode(ByteBuffer, CharBuffer, boolean)
     *             decode(ByteBuffer, CharBuffer, boolean)} with true as value
     *             for the last boolean parameter.
     */
    CARAPI Flush(
        /* [in] */ ICharBuffer* charBuffer,
        /* [out] */ ICoderResult** result);

    /**
     * Indicates whether this decoder implements an auto-detecting charset.
     *
     * @return <code>true</code> if this decoder implements an auto-detecting
     *         charset.
     */
    CARAPI IsAutoDetecting(
        /* [out] */ Boolean* result);

    /**
     * Indicates whether this decoder has detected a charset; this method is
     * optional.
     * <p>
     * If this decoder implements an auto-detecting charset, then this method
     * may start to return true during decoding operation to indicate that a
     * charset has been detected in the input bytes and that the charset can be
     * retrieved by invoking the {@link #detectedCharset() detectedCharset}
     * method.
     * <p>
     * Note that a decoder that implements an auto-detecting charset may still
     * succeed in decoding a portion of the given input even when it is unable
     * to detect the charset. For this reason users should be aware that a
     * <code>false</code> return value does not indicate that no decoding took
     * place.
     * <p>
     * The default implementation always throws an
     * <code>UnsupportedOperationException</code>; it should be overridden by
     * a subclass if needed.
     *
     * @return <code>true</code> if this decoder has detected a charset.
     * @throws UnsupportedOperationException
     *             if this decoder doesn't implement an auto-detecting charset.
     */
    CARAPI IsCharsetDetected(
        /* [out] */ Boolean* result);

    /**
     * Returns this decoder's <code>CodingErrorAction</code> when malformed input
     * occurred during the decoding process.
     */
    CARAPI MalformedInputAction(
        /* [out] */ ICodingErrorAction** codingErrorAction);

    /**
     * Returns the maximum number of characters which can be created by this
     * decoder for one input byte, must be positive.
     */
    CARAPI MaxCharsPerByte(
        /* [out] */ Float* maxNumber);

    /**
     * Sets this decoder's action on malformed input errors.
     *
     * This method will call the
     * {@link #implOnMalformedInput(CodingErrorAction) implOnMalformedInput}
     * method with the given new action as argument.
     *
     * @param newAction
     *            the new action on malformed input error.
     * @return this decoder.
     * @throws IllegalArgumentException
     *             if {@code newAction} is {@code null}.
     */
    CARAPI OnMalformedInput(
        /* [in] */ ICodingErrorAction* newAction);

    /**
     * Sets this decoder's action on unmappable character errors.
     *
     * This method will call the
     * {@link #implOnUnmappableCharacter(CodingErrorAction) implOnUnmappableCharacter}
     * method with the given new action as argument.
     *
     * @param newAction
     *            the new action on unmappable character error.
     * @return this decoder.
     * @throws IllegalArgumentException
     *             if {@code newAction} is {@code null}.
     */
    CARAPI OnUnmappableCharacter(
        /* [in] */ ICodingErrorAction* newAction);

    /**
     * Returns the replacement string, which is never null or empty.
     */
    CARAPI Replacement(
        /* [out] */ String* replacement);

    /**
     * Sets the new replacement string.
     *
     * This method first checks the given replacement's validity, then changes
     * the replacement value, and at last calls the
     * {@link #implReplaceWith(String) implReplaceWith} method with the given
     * new replacement as argument.
     *
     * @param replacement
     *            the replacement string, cannot be null or empty. Its length
     *            cannot be larger than {@link #maxCharsPerByte()}.
     * @return this decoder.
     * @throws IllegalArgumentException
     *             if the given replacement cannot satisfy the requirement
     *             mentioned above.
     */
    CARAPI ReplaceWith(
        /* [in] */ const String& newReplacement);

    /**
     * Resets this decoder. This method will reset the internal status, and then
     * calls <code>implReset()</code> to reset any status related to the
     * specific charset.
     *
     * @return this decoder.
     */
    CARAPI Reset();

    /**
     * Returns this decoder's <code>CodingErrorAction</code> when an unmappable
     * character error occurred during the decoding process.
     */
    CARAPI UnmappableCharacterAction(
        /* [out] */ ICodingErrorAction** codingErrorAction);

protected:
    /**
     * Decodes bytes into characters. This method is called by the decode method.
     *
     * @sa #decode(ByteBuffer, CharBuffer, boolean) decode
     * <p>
     * This method will implement the essential decoding operation, and it won't
     * stop decoding until either all the input bytes are read, the output
     * buffer is filled, or some exception is encountered. Then it will return a
     * <code>CoderResult</code> object indicating the result of current
     * decoding operation. The rules to construct the <code>CoderResult</code>
     * are the same as for decode.
     *
     * @sa #decode(ByteBuffer, CharBuffer, boolean) decode
     * When an exception is encountered in the decoding operation, most implementations
     * of this method will return a relevant result object to thedecode method, and some
     * performance optimized implementation may handle the exception and
     * implement the error action itself.
     *
     * @sa #decode(ByteBuffer, CharBuffer, boolean) decode
     * <p>
     * The buffers are scanned from their current positions, and their positions
     * will be modified accordingly, while their marks and limits will be
     * intact. At most in.remaining() characters will be read, and  out.remaining() bytes
     * will be written.
     *
     * @sa ByteBuffer#remaining() in.remaining()
     * @sa CharBuffer#remaining() out.remaining()
     * <p>
     * Note that some implementations may pre-scan the input buffer and return a
     * <code>CoderResult.UNDERFLOW</code> until it receives sufficient input.
     *
     * @param in
     *            the input buffer.
     * @param out
     *            the output buffer.
     * @return a <code>CoderResult</code> instance indicating the result.
     */
    virtual CARAPI DecodeLoop(
        /* [in] */ IByteBuffer* byteBuffer,
        /* [in] */ ICharBuffer* charBuffer,
        /* [out] */ ICoderResult** result) = 0;

    /**
     * Flushes this decoder. The default implementation does nothing and always
     * returns <code>CoderResult.UNDERFLOW</code>; this method can be
     * overridden if needed.
     *
     * @param out
     *            the output buffer.
     * @return <code>CoderResult.UNDERFLOW</code> or
     *         <code>CoderResult.OVERFLOW</code>.
     */
    virtual CARAPI ImplFlush(
        /* [in] */ ICharBuffer* outInput,
        /* [out] */ ICoderResult** result);

    /**
     * Notifies that this decoder's <code>CodingErrorAction</code> specified
     * for malformed input error has been changed. The default implementation
     * does nothing; this method can be overridden if needed.
     *
     * @param newAction
     *            the new action.
     */
    virtual CARAPI ImplOnMalformedInput(
        /* [in] */ ICodingErrorAction* newAction);

    /**
     * Notifies that this decoder's <code>CodingErrorAction</code> specified
     * for unmappable character error has been changed. The default
     * implementation does nothing; this method can be overridden if needed.
     *
     * @param newAction
     *            the new action.
     */
    virtual CARAPI ImplOnUnmappableCharacter(
        /* [in] */ ICodingErrorAction* newAction);

    /**
     * Notifies that this decoder's replacement has been changed. The default
     * implementation does nothing; this method can be overridden if needed.
     *
     * @param newReplacement
     *            the new replacement string.
     */
    virtual CARAPI ImplReplaceWith(
        /* [in] */ const String& newReplacement);

    /**
     * Reset this decoder's charset related state. The default implementation
     * does nothing; this method can be overridden if needed.
     */
    virtual CARAPI ImplReset();

private:
    /*
     * checks the result whether it needs to throw CharacterCodingException.
     */
    CARAPI CheckCoderResult(
        /* [in] */ ICoderResult* result);

    /*
     * original output is full and doesn't have remaining. allocate more space
     * to new CharBuffer and return it, the contents in the given buffer will be
     * copied into the new buffer.
     */
    CARAPI AllocateMore(
        /* [in] */ ICharBuffer* output,
        /* [out] */ ICharBuffer** newOutput);

private:
    static const String RESET;
    static const String ONGOING;
    static const String END_OF_INPUT;
    static const String FLUSHED;

    AutoPtr<ICharset> mCharset;

    Float mAverageCharsPerByte;
    Float mMaxCharsPerByte;

    String mReplacementChars;

    String mState;

    AutoPtr<ICodingErrorAction> mMalformedInputAction;
    AutoPtr<ICodingErrorAction> mUnmappableCharacterAction;
};

} // namespace CharSet
} // namespace IO
} // namespace Elastos

#endif // __ELASTOS_IO_CHARSET_CHARSETDECODER_H__
