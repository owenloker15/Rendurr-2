#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace Rendurr
{
    enum class ColorAttachmentFormat
    {
        RGBA8
    };

    struct FramebufferSpecification
    {
        uint32_t width;
        uint32_t height;
        std::unordered_map<std::string, ColorAttachmentFormat>
            m_colorAttachments; // id (not used but for access)
    };

    class Framebuffer
    {
    public:
        Framebuffer(FramebufferSpecification spec);
        ~Framebuffer() = default;

        void bind() const;
        void unbind() const;
        void release();
        void resize(uint32_t width, uint32_t height);

        uint32_t getColorAttachmentId(const std::string& colorAttachmentKey) const;

    private:
        void addColorAttachment(const std::string& colorAttachmentKey,
                                const ColorAttachmentFormat& format);

    private:
        std::unordered_map<std::string, uint32_t> m_colorAttachments;
        uint32_t m_rendererId;
        uint32_t m_width = 0;
        uint32_t m_height = 0;
        uint32_t m_depthAttachment = 0;
        uint32_t m_colorAttachmentIndex = 0;
    };
} // namespace Rendurr
