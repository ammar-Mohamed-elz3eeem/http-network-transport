#ifndef __HTTP_NETWORK_TRANSPORT_HPP__
#define __HTTP_NETWORK_TRANSPORT_HPP__

#include <memory>

/**
 * @file: HTTPNetworkTransport.hpp
 * @author: Ammar Massoud (ammar@wpkama.com)
 * 
 * @brief
 *     This file declares class HTTPNetworkTransport::HTTPNetworkTransport
 * 
 * @version: 1.0.0
 * @date: 2024-07-28
 * @copyright: Copyright (c) 2024
 */

namespace HTTPNetworkTransport
{
	class HTTPServerNetworkTransport
	{
	public:
		// Lifecycle Management
		~HTTPServerNetworkTransport() noexcept;
		HTTPServerNetworkTransport(const HTTPServerNetworkTransport &) noexcept = delete;
		HTTPServerNetworkTransport(HTTPServerNetworkTransport &&) noexcept = delete;
		HTTPServerNetworkTransport &operator=(const HTTPServerNetworkTransport &) noexcept = delete;
		HTTPServerNetworkTransport &operator=(HTTPServerNetworkTransport &&) noexcept = delete;

		// Public Methods

		/**
		 * @brief
		 *     Construct a new HTTPServerNetworkTransport object
		 */
		HTTPServerNetworkTransport();

	private:
		// Private Properties
		/**
		 * @brief
		 *     structure to hold all the private properties of the
		 *     HTTPServerNetworkTransport instance.
		 */
		struct Impl;

		/**
		 * @brief
		 *     This contains all private properties of the HTTPServerNetworkTransport
		 *     class.
		 */
		std::unique_ptr<struct Impl> impl_;
	};
} // namespace HTTPNetworkTransport

#endif /* __HTTP_NETWORK_TRANSPORT_HPP__ */