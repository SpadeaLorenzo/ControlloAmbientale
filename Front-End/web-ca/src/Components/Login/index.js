import React from 'react';

import { CSSReset, ThemeProvider } from "@chakra-ui/core"
import customTheme from "./customTheme"
import { Button, Heading, Stack, Text } from "@chakra-ui/core"
const LoginInputs = () => {
    return (
        <Stack spacing={4} bg="white" p={8} borderRadius="lg">
            <Heading as="h1" size="md" color="primary.900">
                Chakra UI is rad!
            </Heading>
            <Text as="p" fontSize="md" color="primary.500">
                Here are your first Chakra components:
            </Text>
            <Button variantColor="primary" isFullWidth>
                Click me, please!
            </Button>
        </Stack>
    );
};

export default LoginInputs;