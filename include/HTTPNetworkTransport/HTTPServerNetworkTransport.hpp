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
	class HTTPNetworkTransport
	{
	public:
		// Lifecycle Management
		~HTTPNetworkTransport() noexcept;
		HTTPNetworkTransport(const HTTPNetworkTransport &) noexcept = delete;
		HTTPNetworkTransport(HTTPNetworkTransport &&) noexcept = delete;
		HTTPNetworkTransport &operator=(const HTTPNetworkTransport &) noexcept = delete;
		HTTPNetworkTransport &operator=(HTTPNetworkTransport &&) noexcept = delete;

		// Public Methods

		/**
		 * @brief
		 *     Construct a new HTTPNetworkTransport object
		 */
		HTTPNetworkTransport();

	private:
		// Private Properties
		/**
		 * @brief
		 *     structure to hold all the private properties of the
		 *     HTTPNetworkTransport instance.
		 */
		struct Impl;

		/**
		 * @brief
		 *     This contains all private properties of the HTTPNetworkTransport
		 *     class.
		 */
		std::unique_ptr<struct Impl> impl_;
	};
} // namespace HTTPNetworkTransport

#endif /* __HTTP_NETWORK_TRANSPORT_HPP__ */